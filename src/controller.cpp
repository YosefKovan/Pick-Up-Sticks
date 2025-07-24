#include "controller.h"
#include <stdexcept>

//==========================================
//              constructer
//==========================================
Controller::Controller()
    :  m_running(true)
{}
//==========================================
//             game controller
//==========================================
void Controller::gameController()
{
    while (m_running)
    {
        switch (m_menu.runMenu())
        {
            case MenuReturnValue::close:
                m_running = false;
                break;
            case MenuReturnValue::play:
            {
                newGame();
                break;
            }
            case MenuReturnValue::load:
            {
                loadGame();
                break;
            }
        }
    }
}
//==========================================
//               new game
//==========================================
void Controller::newGame()
{
    auto screen = Board();
    screen.playGame();
}
//==========================================
//               load game
//==========================================
void Controller::loadGame()
{
    try {
        auto fileDealing = FileDealing();
        auto pair = fileDealing.loadFile();
        auto screen = Board(pair.first, pair.second);
        screen.playGame();
    }
    catch (std::invalid_argument const& ex)
    {
        std::cerr << "Exception: unable to load saved game due to " << ex.what() << std::endl;
    }
    catch (std::out_of_range const& ex)
    {
        std::cerr << "Exception: unable to load saved game due to " << ex.what() << std::endl;
    }
    catch (std::ios_base::failure const& ex)
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
}

