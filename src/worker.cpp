#include "worker.hpp"
#include <mutex>

//-----------------------------------------------------------------------------|
//-- CWorkerThread ------------------------------------------------------------|
//-----------------------------------------------------------------------------|

CWorkerThread::CWorkerThread()
{
    SetRunning(true);

    m_Worker = std::thread([this](){ Loop(); });
}

CWorkerThread::~CWorkerThread()
{
    SetRunning(false);

    m_ConVar.notify_one();
    m_Worker.join();
}

void CWorkerThread::AddCommand(Command&& cmd)
{
    {
        std::lock_guard lock(m_Mutex);
        m_Commands.push(std::move(cmd));
    }
    m_ConVar.notify_one();
}

void CWorkerThread::Loop()
{
    while (m_Running)
    {
        Command cmd;

        {
            std::unique_lock lock(m_Mutex);
            m_ConVar.wait(lock, [this] 
            {
                return !m_Commands.empty() || !m_Running;
            });

            if (!m_Running && m_Commands.empty())
                return;

            cmd = std::move(m_Commands.front());
            m_Commands.pop();
        }

        cmd();
    }
}

void CWorkerThread::SetRunning(bool running)
{
    std::lock_guard lock(m_Mutex);
    m_Running = running;
}