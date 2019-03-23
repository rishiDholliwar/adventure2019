#include <chrono>
#include <iostream>
#include <unistd.h>
#include <string>

#include <Scheduler.h>

// Chrono author himself recommends using their namespace...
// I believe this is fine because it is in the source file
using namespace std::chrono;

inline long getCurrentTime() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Scheduler::schedule(std::shared_ptr<Command> job, int deferral) {
    long currentTime = getCurrentTime();
    long scheduledTime = currentTime + deferral * heartbeatPerMilliseconds;
    jobs.push(std::pair(scheduledTime, job));
}

[[nodiscard]]
std::vector<Response> Scheduler::update() {
    std::vector<Response> res;
    long currentTime = getCurrentTime();
    auto timeToSleep = heartbeatPerMilliseconds - (currentTime - this->lastUpdated);
    if( timeToSleep == 0 ) {
        return res;
    }
    if( timeToSleep > 0 ) {
        sleep(timeToSleep / 1000);
    }
    currentTime = getCurrentTime();
    this->lastUpdated = currentTime;

    while ( ! jobs.empty() && currentTime - jobs.top().first >= 0 ) {
        auto job = jobs.top().second;
        std::vector<Response> responses;
        if( job->callbackable() && job->isCallback() ) {
            auto ret = job->runCallback();
            if( !ret.second && job->callbackable()) {
                this->schedule(job, job->getCallbackTime());
            }
            responses = ret.first;
        } else {
            auto ret = job->execute();
            responses = ret.first;
            if( job->callbackable() && ret.second ) {
                job->setCallback(false);
                this->schedule(job, job->getCallbackTime());
            }
        }

        res.reserve(res.size() + responses.size());
        res.insert(res.end(), responses.begin(), responses.end());

        jobs.pop();
    }
    return res;
}
