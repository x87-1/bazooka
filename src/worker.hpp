#pragma once
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

//-----------------------------------------------------------------------------|
//-- CWorkerThread ------------------------------------------------------------|
//-----------------------------------------------------------------------------|

class CWorkerThread
{
public:
    using Command = std::function<void()>;

    CWorkerThread();
    ~CWorkerThread();

    void AddCommand(Command&& cmd);

private:
    void SetRunning(bool running);
    void Loop();

    std::queue<Command> m_Commands;
    std::condition_variable m_ConVar;
    std::mutex m_Mutex;
    std::thread m_Worker;
    bool m_Running = false;
};