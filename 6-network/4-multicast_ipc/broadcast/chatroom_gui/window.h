#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <ncurses.h>
#include <stdlib.h>
#include <signal.h>

#define PAIR_BKGD 10
#define PAIR_TITLE 20
#define PAIR_TEXT	30

#define PAIR_WHITE  50
#define PAIR_YELLOW 51
#define PAIR_GREEN  52
#define PAIR_RED    53
#define PAIR_BLUE	54
	
typedef struct _windows_ {
	WINDOW *win_in;
	WINDOW *win_out;
	WINDOW *win_list;
	WINDOW *fram_in;
	WINDOW *fram_out;
	WINDOW *fram_list;
}Window_t;

#define USERNAME_LEN     32 
#define PASSWORD_LEN     32
    
typedef struct _passwd_ {
	char pwd_name[USERNAME_LEN];
	char pwd_passwd[PASSWORD_LEN]; 
}WindowPasswd_t;

extern void window_error(void);
extern void window_login(WindowPasswd_t *buff);
extern void window_clear(WINDOW *win);
extern Window_t *window_init(void);
extern void window_destroy(Window_t *win);
extern void window_puts(Window_t *win, const char *str, int pair);
extern void window_gets(Window_t *win, char *buff, int n);

extern void window_show_title(Window_t *win, const char *name, const char *time, const char *addr);
extern void window_show_text(Window_t *win, const char *text);
extern void window_show_list(Window_t *win, const char *list[], int len);

#endif /* __WINDOW_H__ */
