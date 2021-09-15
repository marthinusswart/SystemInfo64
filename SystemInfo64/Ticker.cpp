#include "Ticker.h"

SI64::Ticker::Ticker()
{

}

SI64::Ticker::Ticker(int const& tick_duration, int const& max_tick)
{
	set_tick_duration(tick_duration);
	set_max_tick(max_tick);
	reset();
}

/* Protected */

void SI64::Ticker::calculate()
{
	_end = std::chrono::system_clock::now();
	_elapsed = _end - _start;
	int e = (int)(_elapsed.count() * 1000);
	if (e >= _tick_duration && e > 0)
	{
		_update = true;
		int t = (e - (e % _tick_duration)) / _tick_duration;
		_current_tick += t;
		if (_current_tick >= _max_tick)
		{
			_current_tick = 0;
		}
		_start = _end;
	}
	else
	{
		_update = false;
	}
}

/* Getters */

int SI64::Ticker::get_tick() // Returns current tick
{
	calculate();
	return _current_tick;
}

/* Setters */

void SI64::Ticker::set_tick_duration(int const& d)
{
	_tick_duration = d;
}

void SI64::Ticker::set_max_tick(int const& max)
{
	_max_tick = max;
}

/* Methods */

void SI64::Ticker::start()
{
	reset();
}

void SI64::Ticker::reset()
{
	_update = true;
	_current_tick = 0;
	_start = std::chrono::system_clock::now();
}

bool SI64::Ticker::updated()
{
	return _update;
}