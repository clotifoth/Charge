#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <cstdlib>

#define START 0
#define OPTIONS 1
#define ABOUT 2
#define EXIT 3

WINDOW *create_newwin(int height, int width, int starty, int startx);
WINDOW *create_menuwin(int height, int width);
void main_menu();
void render_main_menu(WINDOW* win, int menu_selection);
static int starty = LINES / 2;	/* Calculating for a center placement */
static int startx = COLS / 2;	/* of the window		*/

int main(int argc, char **argv)
{
	//char c = 0;
	//int ch;

	initscr();
	start_color();
	curs_set(FALSE);
	noecho();		
	cbreak();
	main_menu();
	endwin();
	std::exit(EXIT_SUCCESS);
}

void main_menu()
{
	int parent_y, parent_x;
	int option = START;
	int input;
	// get our maximum window dimensions
	getmaxyx(stdscr, parent_y, parent_x);
	// set up initial windows
	WINDOW *win = newwin(parent_y, parent_x, 0, 0);
	keypad(win, TRUE);
	touchwin(win);
	
	while(1)
	{
		switch(input)
		{
			case KEY_UP:
			{
				if(option <= START) option = EXIT;
				else option--;
				break;
			}
			case KEY_DOWN:
			{
				if(option >= EXIT) option = START;
				else option++;
				break;
			}
			case '\n':
			{
				switch(option)
				{
					case START:
					{
						// Start game
						break;
					}
					case OPTIONS:
					{
						// Options
						break;
					}
					case ABOUT:
					{
						// About
						break;
					}
					case EXIT:
					{
						delwin(win);
						curs_set(TRUE);
						echo();
						endwin();
						std::exit(EXIT_SUCCESS);
					}
					default: break;
				}
				break;
			}
			default: break;
		}
		render_main_menu(win, option);
		input = wgetch(win);
	}
	
	
}

void render_main_menu(WINDOW* win, int menu_selection)
{
	if(has_colors() == FALSE) return;
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	wattron(win, COLOR_PAIR(1) | A_BOLD);
	mvwprintw(win, 2, 13, " CCCCCC  HH  HH   AAAA   RRRRR   GGGGG  EEEEEE  !! ");
	mvwprintw(win, 3, 13, "CCC  CCC HH  HH  AA  AA  RR  RR GG      EE     !!!!");
	mvwprintw(win, 4, 13, "CC       HHHHHH  AAAAAA  RRRRR  GG  GGG EEEE    !! ");
	mvwprintw(win, 5, 13, "CCC  CCC HH  HH AA    AA RR  RR GG   GG EE         ");
	init_pair(2, COLOR_RED, COLOR_BLACK);
	wattroff(win, COLOR_PAIR(1));
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, 6, 13, " CCCCCC  HH  HH AA    AA RR  RR  GGGGG  EEEEEE  !! ");
	
	wattroff(win, A_BOLD | COLOR_PAIR(2));
	/* The integer argument corresponds to which menu choice was selected.
	 * Only this row will be bolded / backgrounded.
	 */
	if(menu_selection == START) wattron(win, A_BOLD | COLOR_PAIR(2));
	mvwprintw(win, 14, 23, "CHAAAAAAAAARGE!");
	if(menu_selection == START) wattroff(win, A_BOLD | COLOR_PAIR(2));
	
	if(menu_selection == OPTIONS) wattron(win, A_BOLD);
	mvwprintw(win, 15, 23, "Options");
	if(menu_selection == OPTIONS) wattroff(win, A_BOLD);
	
	if(menu_selection == ABOUT) wattron(win, A_BOLD);
	mvwprintw(win, 16, 23, "About");
	if(menu_selection == ABOUT) wattroff(win, A_BOLD);
	
	if(menu_selection == EXIT) wattron(win, A_BOLD);
	mvwprintw(win, 17, 23, "Exit");
	if(menu_selection == EXIT) wattroff(win, A_BOLD);
	
	wrefresh(win);
}
