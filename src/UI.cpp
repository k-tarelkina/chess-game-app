#include "UI.h"

UI::UI(RefPtr<Window> window) : window_(window), uiObservers_(std::vector<UIObserver *>(0))
{
  overlay_ = Overlay::Create(window_, 1, 1, 0, 0);
  view()->LoadURL("file:///app.html");

  // Force view to resize to match the window
  OnResize(window_.get(), window_->width(), window_->height());

  view()->set_load_listener(this);
}

UI::~UI()
{
  view()->set_load_listener(nullptr);
  view()->set_view_listener(nullptr);
}

void UI::OnDOMReady(ultralight::View *caller,
                    uint64_t frame_id,
                    bool is_main_frame,
                    const String &url)
{
  RefPtr<JSContext> locked_context = view()->LockJSContext();
  SetJSContext(locked_context->ctx());

  JSObject global = JSGlobalObject();

  global["onCellClicked"] = BindJSCallback(&UI::onCellClicked);
  global["onStartGame"] = BindJSCallback(&UI::onStartGame);
  global["onStartGameOver"] = BindJSCallback(&UI::onStartGameOver);
  global["onAddWhitePiecesUser"] = BindJSCallback(&UI::onAddWhitePiecesUser);
  global["onAddBlackPiecesUser"] = BindJSCallback(&UI::onAddBlackPiecesUser);

  for (auto observer : uiObservers_)
  {
    observer->onUiReady();
  }
}

void UI::OnResize(ultralight::Window *window, uint32_t width, uint32_t height)
{
  overlay_->Resize(width, height);
}

void UI::attachObserver(UIObserver *observer)
{
  uiObservers_.push_back(observer);
}

void UI::onCellClicked(const JSObject &obj, const JSArgs &args)
{
  for (auto observer : uiObservers_)
  {
    observer->onCellClicked(args[0], args[1]);
  }
}

void UI::onStartGame(const JSObject &obj, const JSArgs &args)
{
  for (auto observer : uiObservers_)
  {
    observer->onStartGame();
  }
}

void UI::onStartGameOver(const JSObject &obj, const JSArgs &args)
{
  for (auto observer : uiObservers_)
  {
    observer->onStartGameOver();
  }
}

void UI::onAddWhitePiecesUser(const JSObject &obj, const JSArgs &args)
{
  for (auto observer : uiObservers_)
  {
    auto username = String(args[0]).utf8().data();
    observer->onAddWhitePiecesUser(username);
  }
}

void UI::onAddBlackPiecesUser(const JSObject &obj, const JSArgs &args)
{
  for (auto observer : uiObservers_)
  {
    auto username = String(args[0]).utf8().data();
    observer->onAddBlackPiecesUser(username);
  }
}

void UI::putPiece(int x, int y, const std::string &pieceName, Color color)
{
  std::string command = "putPiece(" +
                        std::to_string(x) + ", " +
                        std::to_string(y) + ", \"" +
                        pieceName + "\", \"" +
                        colorToString(color) + "\")";
  view()->EvaluateScript(command.c_str());
}

void UI::addDeadPiece(const std::string &pieceName, Color color)
{
  std::string command = "addDeadPiece(\"" + pieceName + "\", \"" +
                        colorToString(color) + "\")";
  view()->EvaluateScript(command.c_str());
}

void UI::removePiece(int x, int y)
{
  std::string command = "removePiece(" +
                        std::to_string(x) + ", " +
                        std::to_string(y) + ")";
  view()->EvaluateScript(command.c_str());
}

void UI::clearCellsHighlight()
{
  std::string command = "clearCellsHighlight()";
  view()->EvaluateScript(command.c_str());
}

void UI::highlightSelectedCell(int x, int y)
{
  std::string command = "highlightSelectedCell(" + std::to_string(x) + "," +
                        std::to_string(y) + ")";
  view()->EvaluateScript(command.c_str());
}

void UI::highlightCells(const std::vector<Coordinates> &coordinates)
{
  std::string command = "highlightCells([";

  for (int i = 0; i < coordinates.size(); i++)
  {
    auto c = coordinates[i];
    command = command + "[" + std::to_string(c.first) + "," + std::to_string(c.second) + "]";
    if (i < coordinates.size() - 1)
      command = command + ",";
  }

  command = command + "])";
  view()->EvaluateScript(command.c_str());
}

void UI::showMessage(const std::string &message)
{
  std::string command = "showMessage(\"" + message + "\")";
  view()->EvaluateScript(command.c_str());
}

void UI::clearMessage()
{
  view()->EvaluateScript("clearMessage()");
}

void UI::clearBoard()
{
  view()->EvaluateScript("clearBoard()");
}

void UI::clearUserNames()
{
  view()->EvaluateScript("clearUserNames()");
}

void UI::startTimer()
{
  view()->EvaluateScript("startTimer()");
}

void UI::resetTimer()
{
  view()->EvaluateScript("resetTimer()");
}

void UI::stopTimer()
{
  view()->EvaluateScript("stopTimer()");
}