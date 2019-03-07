#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <functional>
#include <vector>
#include <queue>
#include <utility>
#include <memory>

#include <Command.h>
#include <Response.h>

using Job = std::pair<long, std::shared_ptr<Command>>;

struct LessThanByJob
{
  bool operator()(const Job& lhs, const Job& rhs) const
  {
    return lhs.first > rhs.first;
  }
};

class Scheduler
{
public:
    Scheduler(long heartbeat):heartbeatPerMilliseconds(heartbeat){};
    ~Scheduler() = default;
    void schedule(std::shared_ptr<Command> job, int deferral);
    [[nodiscard]] std::vector<Response> update();
private:
    long heartbeatPerMilliseconds;
    std::priority_queue<Job, std::vector<Job>, LessThanByJob> jobs;
    long lastUpdated = 0;
};

#endif //SCHEDULER_H
