#include <breakout/view/GameView.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>

namespace breakout::view {

auto GameView::exit_main_loop() -> void {
  m_screen.Exit();
}

auto GameView::update_screen_renderer(ftxui::Component renderer) -> void {
  exit_main_loop();
  m_screen.Loop(renderer);
}

auto GameView::render_main_menu(model::GameStateMainMenu const&, MainMenuHandlers const &h) -> void {
  using namespace ftxui;

  auto p_play_button = Button("  Play  ", [&h]() -> void { h.handle_play_button(); }, ButtonOption::Simple());
  auto p_quit_button = Button("  Quit  ", [&h]() -> void { h.handle_quit_button(); }, ButtonOption::Simple());

  auto container = Container::Vertical({
    p_play_button,
    p_quit_button,
  });

  auto component = Renderer(container, [&]() -> Element {
    FlexboxConfig config;
    config.direction = FlexboxConfig::Direction::Column;
    config.wrap = FlexboxConfig::Wrap::NoWrap;
    config.justify_content = FlexboxConfig::JustifyContent::Center;
    config.align_items = FlexboxConfig::AlignItems::Center;
    config.align_content = FlexboxConfig::AlignContent::Center;
    config.SetGap(0, 1);

    return flexbox({
      vbox({
        text(R"(                                                )"),
        text(R"(    ____                 _               _      )"),
        text(R"(   | __ ) _ __ ___  __ _| | _____  _   _| |_    )"),
        text(R"(   |  _ \| '__/ _ \/ _` | |/ / _ \| | | | __|   )"),
        text(R"(   | |_) | | |  __/ (_| |   < (_) | |_| | |_    )"),
        text(R"(   |____/|_|  \___|\__,_|_|\_\___/ \__,_|\__|   )"),
        text(R"(                                                )"),
        text(R"(                                                )"),
      }) | borderRounded,
      p_play_button->Render(),
      p_quit_button->Render(),
    }, config);
  });

  update_screen_renderer(component);
}

auto GameView::render_pause_menu(model::GameStatePauseMenu const&)-> void {
  std::cout << "Rendering pause menu!\n";
}

auto GameView::render_game_starting(model::GameStateStarting const&) -> void {

  std::cout << "Rendering game starting!\n";
}

auto GameView::render_game_active(model::GameStateActive const&) -> void {
  std::cout << "Rendering active game!\n";
}


} // namespace breakout::view
