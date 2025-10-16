#include "gui/GUI.h"
#include "state.h"

int main(int argc, char *argv[]) {
    GameState gs;
    init_gui(&gs, GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);

    while(gs.should_continue) {
        read_input(&gs);
    }

    free_gui(&gs);
    return 0;
}
