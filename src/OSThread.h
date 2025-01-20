#pragma once

#include <stdint.h>
#include "Thread.h"

namespace concurrency
{
    class BinarySemaphore
    {
    public:
        virtual void wait() = 0;
        virtual void signal() = 0;
    };

    class OSThread
    {
    public:
        /**
         * The entry point that each thread will run once and terminate once it returns.
         * 
         * @return int32_t 
         */
        virtual int32_t runOnce() = 0;

        /**
         * @brief Wait for notification to enter run loop.
         * 
         * @return true if the event was received
         */
        bool waitForEvent() {
            event.wait();
            return true;
        }

        /**
         * @brief Trigger the event to unblock a waiting thread.
         */
        void triggerEvent() {
            event.signal();
        }

        // TODO: Implement these on other platforms.
        /**
         * @brief Get the priority of the thread
         * 
         * @return int32_t 
         */
        virtual int32_t getPriority() = 0;
        /**
         * @brief Set the priority of the thread
         * 
         * @param newPriority 
         */
        virtual void setPriority(int32_t newPriority) = 0;

        virtual void onBeforeStart() {}

    protected:
        BinarySemaphore event;
    };
}