#include <stdio.h>
#include <wiringPi.h>
#include "lpd8806led.h"
#include <math.h>
#include <errno.h>

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

const int greenPin = 23;
const int redPin = 18;
const int butPin = 22;
const int P1[3] = { 18, 23, 24 };
const int P2[3] = { 17, 27, 22 };
const char *targets[3] = { "small", "medium", "large" };
const int scores[3] = { 8, 5, 3 };

static const char *device = "/dev/spidev0.0";
static const int leds = 500;


int
main (void)
{
  int i, l;
  int p1_score = 0;
  int p2_score = 0;
  int game_is_on = 1;

  lpd8806_buffer buf;
  int fd;
  int return_value;
  lpd8806_color *p;

  double h, r, g, b;

  fd = open (device, O_WRONLY);
  if (fd < 0)
    {
      fprintf (stderr, "Error %d: %s\n", errno, strerror (errno));
      exit (1);
    }

  /* Initialize the SPI bus for Total Control Lighting */
  return_value = spi_init (fd);
  if (return_value == -1)
    {
      fprintf (stderr, "SPI initialization error %d: %s\n", errno,
	       strerror (errno));
      exit (1);
    }

  /* Initialize pixel buffer */
  if (lpd8806_init (&buf, leds) < 0)
    {
      fprintf (stderr,
	       "Pixel buffer initialization error: Not enough memory.\n");
      exit (1);
    }

  /* Set the gamma correction factors for each color */
  set_gamma (2.2, 2.2, 2.2);


  wiringPiSetupGpio ();
  pinMode (greenPin, OUTPUT);
  pinMode (redPin, OUTPUT);
  for (i = 0; i < 3; i++)
    {
      pinMode (P1[i], INPUT);
      pinMode (P2[i], INPUT);
      pullUpDnControl (P1[i], PUD_UP);
      pullUpDnControl (P2[i], PUD_UP);
    }
  pwmWrite (redPin, 255);
  pwmWrite (greenPin, 255);

  while (game_is_on)
    {
      for (i = 0; i < leds; i++)
	{
	  write_gamma_color (&buf.pixels[i], 0x00, 0x00, 0x00);
	}
      p1_score = 0;
      p2_score = 0;
      for (i = 0; i < 3; i++)
	{
	  if (digitalRead (P1[i]))
	    {
	      //printf("P1 : %s ",targets[i]);
	    }
	  else
	    {
	      p1_score += scores[i];
	    }
	  if (digitalRead (P2[i]))
	    {
	      //printf("P2 : %s ",targets[i]);
	    }
	  else
	    {
	      p2_score += scores[i];
	    }
	}
      for (i = 0; i < p1_score; i++)
	{
	  write_gamma_color (&buf.pixels[14 - i], 0x00, 0xFF, 0x00);
	}
      for (i = 0; i < p2_score; i++)
	{
	  write_gamma_color (&buf.pixels[15 + i], 0x00, 0x00, 0xFF);
	}
      send_buffer (fd, &buf);
      if (p1_score > 15 || p2_score > 15)
	{
	  game_is_on = 0;
	}
      else
	{
	  delay (75);
	}
    }

  for (l = 0; l < 10; l++)
    {
      for (i = 0; i < leds; i++)
	{
	  write_gamma_color (&buf.pixels[i], 0x00, 0x00, 0x00);
	}
      send_buffer (fd, &buf);
      delay (250);
      for (i = 0; i < leds; i++)
	{
	  write_gamma_color (&buf.pixels[i], 0x00,
			     p1_score > p2_score ? 0xFF : 0X00,
			     p1_score > p2_score ? 0x00 : 0xFF);
	}
      send_buffer (fd, &buf);
      delay (250);
    }
  for (i = 0; i < leds; i++)
    {
      write_gamma_color (&buf.pixels[i], 0x00, 0x00, 0x00);
    }
  send_buffer (fd, &buf);
  lpd8806_free (&buf);
  close (fd);
  return 0;
}
