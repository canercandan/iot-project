// http://library.gnome.org/devel/gtkmm-tutorial/unstable/sec-timeouts.html.en

#include <gtkmm.h>
#include <iostream>
#include <map>

class TimerExample : public Gtk::Window
{
public:
  TimerExample();

protected:
  // signal handlers
  void on_button_add_timer();
  void on_button_delete_timer();
  void on_button_quit();

  // This is the callback function the timeout will call
  bool on_timeout(int timer_number);

  // Member data:

  Gtk::HBox m_Box;
  Gtk::Button m_ButtonAddTimer, m_ButtonDeleteTimer, m_ButtonQuit;

  // Keep track of the timers being added:
  int m_timer_number;

  // These two constants are initialized in the constructor's member initializer:
  const int count_value;
  const int timeout_value;

  // STL map for storing our connections
  std::map<int, sigc::connection> m_timers;

  // STL map for storing our timer values.
  // Each timer counts back from COUNT_VALUE to 0 and is removed when it reaches 0
  std::map<int, int> m_counters;
};

TimerExample::TimerExample() :
  m_Box(true, 10),
  // use Gtk::Stock wherever possible for buttons, etc.
  m_ButtonAddTimer(Gtk::Stock::ADD),
  m_ButtonDeleteTimer(Gtk::Stock::REMOVE),
  m_ButtonQuit(Gtk::Stock::QUIT),
  m_timer_number(0), // start numbering the timers at 0
  count_value(5), // each timer will count down 5 times before disconnecting
  timeout_value(1500) // 1500 ms = 1.5 seconds
{
  set_border_width(10);

  add(m_Box);
  m_Box.pack_start(m_ButtonAddTimer);
  m_Box.pack_start(m_ButtonDeleteTimer);
  m_Box.pack_start(m_ButtonQuit);

  // Connect the three buttons:
  m_ButtonQuit.signal_clicked().connect(sigc::mem_fun(*this,
						      &TimerExample::on_button_quit));
  m_ButtonAddTimer.signal_clicked().connect(sigc::mem_fun(*this,
							  &TimerExample::on_button_add_timer));
  m_ButtonDeleteTimer.signal_clicked().connect(sigc::mem_fun(*this,
							     &TimerExample::on_button_delete_timer));

  show_all_children();
}

void TimerExample::on_button_quit()
{
  hide();
}

void TimerExample::on_button_add_timer()
{
  // Creation of a new object prevents long lines and shows us a little
  // how slots work.  We have 0 parameters and bool as a return value
  // after calling sigc::bind.
  sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this,
						      &TimerExample::on_timeout), m_timer_number);

  // This is where we connect the slot to the Glib::signal_timeout()
  sigc::connection conn = Glib::signal_timeout().connect(my_slot,
							 timeout_value);

  // Remember the connection:
  m_timers[m_timer_number] = conn;

  // Initialize timer count:
  m_counters[m_timer_number] = count_value + 1;

  // Print some info to the console for the user:
  std::cout << "added timeout " << m_timer_number++ << std::endl;
}

void TimerExample::on_button_delete_timer()
{
  // any timers?
  if(m_timers.empty())
    {
      // no timers left
      std::cout << "Sorry, there are no timers left." << std::endl;
    }
  else
    {
      // get the number of the first timer
      int timer_number = m_timers.begin()->first;

      // Give some info to the user:
      std::cout << "manually disconnecting timer " << timer_number
		<< std::endl;

      // Remove the entry in the counter values
      m_counters.erase(timer_number);

      // Diconnect the signal handler:
      m_timers[timer_number].disconnect();

      // Forget the connection:
      m_timers.erase(timer_number);
    }
}

bool TimerExample::on_timeout(int timer_number)
{
  // Print the timer:
  std::cout << "This is timer " << timer_number;

  // decrement and check counter value
  if (--m_counters[timer_number] == 0)
    {
      std::cout << " being disconnected" <<  std::endl;

      // delete the counter entry in the STL MAP
      m_counters.erase(timer_number);

      // delete the connection entry in the STL MAP
      m_timers.erase(timer_number);

      // Note that we do not have to explicitly call disconnect() on the
      // connection since Gtk::Main does this for us when we return false.
      return false;
    }

  // Print the timer value
  std::cout << " - " << m_counters[timer_number] << "/"
	    << count_value << std::endl;

  // Keep going (do not disconnect yet):
  return true;
}

int main (int argc, char *argv[])
{
  Gtk::Main app(argc, argv);

  TimerExample example;
  Gtk::Main::run(example);

  return 0;
}
