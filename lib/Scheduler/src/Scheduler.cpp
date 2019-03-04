#include <chrono>
#include <iostream>
#include <unistd.h>
#include <string>

#include <Scheduler.h>

// Chrono author himself recommends using their namespace...
// I believe this is fine because it is in the source file
using namespace std::chrono;

inline long getCurrentTime()
{
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Scheduler::schedule(std::unique_ptr<Command> job, int deferral)
{
    long currentTime = getCurrentTime();
    long scheduledTime = currentTime + deferral * heartbeatPerMilliseconds;
    jobs.push(std::pair(scheduledTime, job->clone()));
}

[[nodiscard]]
std::vector<Response> Scheduler::update()
{
    std::vector<Response> res;
    long currentTime = getCurrentTime();
    auto timeToSleep = heartbeatPerMilliseconds - (currentTime - this->lastUpdated);
    if( timeToSleep == 0 )
    {
        std::cout << "Some idiot probably has an Scheduler::update scheduled" << std::endl;
        return res;
    }
    if( timeToSleep > 0 )
    {
        // std::cout << timeToSleep << std::endl;
        sleep(timeToSleep / 1000);
    }
    currentTime = getCurrentTime();
    this->lastUpdated = currentTime;
    while ( ! jobs.empty() )
    {
        if( currentTime - jobs.top().first < 0 )
        {
            break;
        }
        auto job = jobs.top().second->clone();
        auto [responses, result] = job->execute();
        if ( result && job->hasCallback() && job->runCallback() ) {
            job->setCallback(true);
            this->schedule(std::move(job), job->getCallbackTime());
        }

        res.reserve(res.size() + responses.size());
        res.insert(res.end(), responses.begin(), responses.end());

        jobs.pop();
    }
    return res;
}
