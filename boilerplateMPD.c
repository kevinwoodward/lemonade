//Need to figure out what each header is for
#include <mpd/client.h>
#include <mpd/status.h>
#include <mpd/entity.h>
#include <mpd/search.h>
#include <mpd/tag.h>
#include <mpd/message.h>
#include <mpd/connection.h>

#include <stdio.h>

int main()
{
  struct mpd_connection *conn;
  //Create a new connection at the specified address
  conn = mpd_connection_new("127.0.0.1",0,30000);

  //Error check
  if(mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS)
  {
    printf("Connection Failed!\n");
  }


  return 0;
}
