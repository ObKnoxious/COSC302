:wq
#include ...

class city;

operator>>(city) { }
operator<<city) { }

class costtable;

read_cityinfo() { }
write_cityinfo() { }

write_distancetable() { }
write_timetable() { }

create_citygraph() { }
write_citygraph() { }

dijkstra_route() { }

int main(int argc, char *argv[])
{
  commandline option decoding

  city graph declarations

  read_cityinfo()

  set up costtables

  create_citygraph()

  if (mode == graphinfo) {
    write_cityinfo()

    write_distancetable()
    write_timetable()

	write_citygraph()

	return from program
  }

  while (not done) {
	enter> from, to cities
    dijkstra_route(costmode,from,to) 
  }
}
