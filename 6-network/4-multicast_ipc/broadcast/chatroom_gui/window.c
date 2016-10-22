#include "window.h"

void window_error(void)
{ 
    WINDOW  *win; 
	int x,y;
	
    initscr();  /* init ncurses mode */ 
	
    start_color(); 
    init_pair(1, COLOR_BLACK, COLOR_WHITE); 
    init_pair(2, COLOR_YELLOW, COLOR_BLUE); 
    init_pair(3, COLOR_YELLOW, COLOR_RED); 
	
	getmaxyx(stdscr, y, x);
	y = (y - 8) / 2.0;
	x = (x - 27) / 2.0;
    win = newwin(8, 27, y, x); 
	
    wbkgd(win, COLOR_PAIR(3)); 
    box(win, 0, 0); 
   // wbkgdset(win, COLOR_PAIR(1)); 
    mvwprintw(win, 2, 6, "!!!! ERROR !!!!");
    mvwprintw(win, 4, 6, "Enter For Quit."); 
    wrefresh(win); 
#if 0
    mvwprintw(win, 2, 2, "User:"); 
    mvwprintw(win, 4, 2, "Pass:"); 
    wbkgdset(win, COLOR_PAIR(1)); 
    mvwprintw(win, 2, 8, "                "); 
    mvwprintw(win, 4, 8, "                "); 
    wrefresh(win); 
    mvwgetnstr(win, 2, 8, buff->pwd_name, USERNAME_LEN); 
    noecho(); 
    mvwgetnstr(win, 4, 8, buff->pwd_passwd, PASSWORD_LEN); 
    overwrite(win, stdscr); 
	echo();
#endif
	getchar();
    delwin(win); 
	touchwin(stdscr); 

    endwin();  /* leave ncurses mode */ 

} 

void window_login(WindowPasswd_t *buff)
{ 
    WINDOW  *win; 
	int x,y;
	
    initscr();  /* init ncurses mode */ 
	
    start_color(); 
    init_pair(1, COLOR_BLACK, COLOR_WHITE); 
    init_pair(2, COLOR_YELLOW, COLOR_BLUE); 
	
	getmaxyx(stdscr, y, x);
	y = (y - 8) / 2.0;
	x = (x - 27) / 2.0;
    win = newwin(8, 27, y, x); 
	
    wbkgd(win, COLOR_PAIR(2)); 
    box(win, 0, 0); 
    mvwprintw(win, 2, 2, "User:"); 
    mvwprintw(win, 4, 2, "Pass:"); 
    wbkgdset(win, COLOR_PAIR(1)); 
    mvwprintw(win, 2, 8, "                "); 
    mvwprintw(win, 4, 8, "                "); 
    wrefresh(win); 
    mvwgetnstr(win, 2, 8, buff->pwd_name, USERNAME_LEN); 
    noecho(); 
    mvwgetnstr(win, 4, 8, buff->pwd_passwd, PASSWORD_LEN); 
    overwrite(win, stdscr); 
	echo();

    delwin(win); 
	touchwin(stdscr); 

    endwin();  /* leave ncurses mode */ 

} 

Window_t *window_init(void)
{
	Window_t *win;
	int x, y;

	win = malloc(sizeof(*win));
	
	signal(SIGINT, SIG_IGN);
	initscr();
	cbreak();
	
	start_color();
	init_pair(PAIR_BKGD, COLOR_WHITE, 0);
	init_pair(PAIR_TITLE, COLOR_RED, 0);
	init_pair(PAIR_TEXT, COLOR_YELLOW, 0);
	init_pair(PAIR_BLUE, COLOR_BLUE, 0);
	init_pair(PAIR_YELLOW, COLOR_YELLOW, 0);
	init_pair(PAIR_RED, COLOR_RED, 0);
	init_pair(PAIR_GREEN, COLOR_GREEN, 0);
	init_pair(PAIR_WHITE, COLOR_WHITE, 0);

	getmaxyx(stdscr, y, x);
	win->fram_list = newwin(y, x/4.0, 0, 0);
	win->fram_out = newwin(y/4.0*3.0, x/4.0*3.0, 0, x/4.0);
	win->fram_in = newwin(y/4.0, x/4.0*3.0, y/4.0*3.0, x/4.0);
	
	wattron(win->fram_list, COLOR_PAIR(PAIR_YELLOW));
	box(win->fram_list, 0, 0);
	wattron(win->fram_in, COLOR_PAIR(PAIR_GREEN));
	box(win->fram_in, 0, 0);
	wattron(win->fram_out, COLOR_PAIR(PAIR_BLUE));
	box(win->fram_out, 0, 0);
	
	win->win_list = newwin(y-2, x/4.0-2, 1, 1);
	win->win_out = newwin(y/4.0*3.0-2, x/4.0*3.0-2, 1, x/4.0+1);
	win->win_in = newwin(y/4.0-2, x/4.0*3.0-2, y/4.0*3.0+1, x/4.0+1);
	
	wrefresh(win->fram_list);
	wrefresh(win->fram_in);	
	wrefresh(win->fram_out);
	wrefresh(win->win_in);
	wrefresh(win->win_out);
	wrefresh(win->win_list);

	move(y/4.0*3.0, x/4.0);
	return win;
}

void window_destroy(Window_t *win)
{
	delwin(win->win_in);
	delwin(win->win_out);
	delwin(win->win_list);
	delwin(win->fram_in);
	delwin(win->fram_out);
	delwin(win->fram_list);
	endwin();
	free(win);
	signal(SIGINT, SIG_DFL);
}

void window_clear(WINDOW *win)
{
	int i = 0;
	int x, y;
	
	getmaxyx(win, x, y);
	while (i < y)
		mvwprintw(win, i++, 0, "\n");
	mvwprintw(win, 0, 0, "\r");
}

void window_puts(Window_t *win, const char *str, int pair)
{
	int my = 0, mx = 0;
	int x, y;

	getmaxyx(win->win_out, my, mx);
	getyx(win->win_out, y, x);
	if (y > my-2)
		window_clear(win->win_out);

	wattron(win->win_out, COLOR_PAIR(pair));
	waddstr(win->win_out, str);
	wrefresh(win->win_out);
	wattroff(win->win_out, COLOR_PAIR(pair));
}

void window_gets(Window_t *win, char *buff, int n)
{
	int my = 0, mx = 0;
	int y, x;
	
	wgetnstr(win->win_in, buff, n);
	wrefresh(win->win_in);

	getmaxyx(win->win_in, my, mx);
	getyx(win->win_in, y, x);
	//if (y > my-2)
		window_clear(win->win_in);
	
	wrefresh(win->win_in);	
}

void window_show_title(Window_t *win, const char *name, const char *time, const char *addr)
{
#if 0
	wattron(win->win_out, COLOR_PAIR(PAIR_RED));
	waddstr(win->win_out, name);
	
	wattron(win->win_out, COLOR_PAIR(PAIR_GREEN));
	waddch(win->win_out, '@');

	wattron(win->win_out, COLOR_PAIR(PAIR_YELLOW));
	waddstr(win->win_out, time);

	wattron(win->win_out, COLOR_PAIR(PAIR_BLUE));
	waddch(win->win_out, '[');
	waddstr(win->win_out, addr);
	waddch(win->win_out, ']');
	waddch(win->win_out, '\n');

#else
	window_puts(win, name, PAIR_RED);
	window_puts(win, "@", PAIR_GREEN);
	window_puts(win, time, PAIR_YELLOW);
	window_puts(win, "[", PAIR_GREEN);
	window_puts(win, addr, PAIR_BLUE);
	window_puts(win, "]\n", PAIR_GREEN);
#endif
	wrefresh(win->win_out);
}

void window_show_text(Window_t *win, const char *text)
{
	waddch(win->win_out, '\t');
	window_puts(win, text, PAIR_WHITE);
	waddch(win->win_out, '\n');
}

void window_show_list(Window_t *win, const char *list[], int len)
{
	int i;

	window_clear(win->win_list);

	wattron(win->win_list, COLOR_PAIR(PAIR_RED));
	wprintw(win->win_list, "User Online: %d\n\n", len);

	wattron(win->win_list, COLOR_PAIR(PAIR_BLUE));
	for (i = 0; i < len; i++)
		wprintw(win->win_list, "%2d. %s\n", i+1, list[i]);
	wattroff(win->win_list, COLOR_PAIR(PAIR_BLUE));

	wrefresh(win->win_list);

}
