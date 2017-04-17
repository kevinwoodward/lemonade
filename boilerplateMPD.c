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

  //Check to make sure connection was sucessful
  if(mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS)
  {
    printf("Connection Failed!\n");
  }

  //Holds info about mpd status
  struct mpd_status * status;
  //Holds info about song
  struct mpd_song * song;
  //Holds an Entitity?
  struct mpd_entity * entity;
  //Holds info about audio format?
  const struct mpd_audio_format * audio_format;
  //Holds info about the playlist
  const struct mpd_playlist * pl;

  //Starts a list of commands?
  mpd_command_list_begin(conn, true);
  mpd_send_status(conn);
  mpd_command_list_end(conn);

  status = mpd_recv_status(conn);


  if(status == NULL)
  {
    printf("Error with status");
  }

  printf("queue length: %i\n", mpd_status_get_queue_length(status));

  return 0;
}
