import curses
import curses.textpad
from todo import TaskManager

# KEY DEFINITIONS
KEY_QUIT = ord('q')
KEY_ADD = ord('a')
KEY_DEL = ord('d')
KEY_TOGGLE = ord(' ')
KEY_CLEAR = ord('c')
KEY_REFRESH = ord('r')

class TaskTUI:
    def __init__(self, stdscr):
        self.stdscr = stdscr
        self.tm = TaskManager()
        try:
            self.tm.load()
        except Exception:
            pass  # Graceful on first run
        self.selected = 0
        curses.curs_set(0)  # Hide cursor

    def run(self):
        while True:
            self.draw()
            key = self.stdscr.getch()

            if key in (KEY_QUIT, 27):  # 27 is ESC
                break
            elif key == curses.KEY_DOWN:
                self.selected = min(self.selected + 1, self.tm.taskCount() - 1)
            elif key == curses.KEY_UP:
                self.selected = max(self.selected - 1, 0)
            elif key == KEY_ADD:
                self.handle_add_task()
            elif key == KEY_DEL:
                self.handle_delete_task()
            elif key == KEY_TOGGLE:
                self.handle_toggle_task()
            elif key == KEY_CLEAR:
                self.handle_clear_tasks()
            elif key == KEY_REFRESH:
                try:
                    self.tm.load()
                except Exception:
                    pass

    def draw(self):
        self.stdscr.clear()
        max_y, max_x = self.stdscr.getmaxyx()

        # Header
        title = "TASK MANAGER (a:Add d:Delete SPACE:Toggle c:Clear q:Quit)"
        self.stdscr.addstr(0, 0, title[:max_x-1], curses.A_BOLD | curses.color_pair(1))
        self.stdscr.hline(1, 0, curses.ACS_HLINE, max_x)

        # Task List
        if self.tm.taskCount() == 0:
            self.stdscr.addstr(3, 2, "No tasks found. Press 'a' to add a new task.", curses.A_DIM)
        else:
            for idx, task in enumerate(self.tm.tasks):
                status = "[X]" if task.completed else "[ ]"
                line = f"{idx+1:2d}. {status} {task.name} - {task.desc} ({task.created})"
                if idx == self.selected:
                    self.stdscr.attron(curses.A_REVERSE)
                    self.stdscr.addstr(3 + idx, 2, line[:max_x-4])
                    self.stdscr.attroff(curses.A_REVERSE)
                else:
                    self.stdscr.addstr(3 + idx, 2, line[:max_x-4])

        # Footer
        self.stdscr.hline(max_y-2, 0, curses.ACS_HLINE, max_x)
        self.stdscr.addstr(max_y-1, 0, "↑/↓ Navigate | a:Add | d:Delete | SPACE:Toggle | c:Clear | q:Quit", curses.A_DIM)

        self.stdscr.refresh()

    def handle_add_task(self):
        name, desc = self.prompt_task_input()
        if name:
            self.tm.addTask(name, desc)
            self.selected = self.tm.taskCount() - 1

    def handle_delete_task(self):
        if self.tm.taskCount() == 0: return
        idx = self.selected
        self.tm.deleteTask(idx)
        self.selected = max(0, self.selected - 1)

    def handle_toggle_task(self):
        if self.tm.taskCount() == 0: return
        self.tm.toggleCompletion(self.selected)

    def handle_clear_tasks(self):
        confirm = self.prompt_yes_no("Clear ALL tasks? (y/n): ")
        if confirm:
            self.tm.clearTasks()
            self.selected = 0

    def prompt_task_input(self):
        max_y, max_x = self.stdscr.getmaxyx()
        h, w = 8, max(40, max_x // 3)
        win = curses.newwin(h, w, (max_y-h)//2, (max_x-w)//2)
        win.border()
        win.addstr(1, 2, "Enter Task Name:")
        name_box = curses.textpad.Textbox(win.derwin(1, w-4, 2, 2))
        win.addstr(4, 2, "Enter Description:")
        desc_box = curses.textpad.Textbox(win.derwin(1, w-4, 5, 2))
        win.refresh()
        name = name_box.edit().strip()
        desc = desc_box.edit().strip()
        return name, desc

    def prompt_yes_no(self, prompt):
        max_y, max_x = self.stdscr.getmaxyx()
        h, w = 3, len(prompt) + 6
        win = curses.newwin(h, w, (max_y-h)//2, (max_x-w)//2)
        win.border()
        win.addstr(1, 2, prompt)
        win.refresh()
        while True:
            k = win.getch()
            if k in (ord('y'), ord('Y')):
                return True
            elif k in (ord('n'), ord('N')):
                return False

def main(stdscr):
    curses.start_color()
    curses.init_pair(1, curses.COLOR_MAGENTA, curses.COLOR_BLACK)
    app = TaskTUI(stdscr)
    app.run()

if __name__ == '__main__':
    curses.wrapper(main)

