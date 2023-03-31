#pragma once

/**
 * A call for measuring time 
 */
class Timer
{
    private:
    /**
   * The clock time when the timer started
   */
    int startTicks;
    /**
   * is the timer running
   */
    bool started;
    public:
    Timer();
   /**
   * starts the timer
   */
    void start();

   /**
   * return the passed ticks since the last start
   * @return the passed ticks in ms
   */
    int get_ticks() const;
};
