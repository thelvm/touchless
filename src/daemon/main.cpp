#include "touchless.hpp"
#include "touchless_gdbus_proxy.h"

Glib::RefPtr<com::thelvm::touchlessProxy> proxy;
touchless::GestureParser gestureParser;

void proxy_created(const Glib::RefPtr<Gio::AsyncResult> &result) {
  std::cout << "Proxy created" << std::endl;
  proxy = com::thelvm::touchlessProxy::createForBusFinish(result);
  gestureParser.SetOnGestureCallback([&](const std::string& gesture_name){
    proxy->gesture_detected_signal.emit(gesture_name);
  });
}

int main(int argc, char **argv) {
  Glib::init();
  Gio::init();

  com::thelvm::touchlessProxy::createForBus(Gio::DBus::BUS_TYPE_SESSION,
                                            Gio::DBus::PROXY_FLAGS_NONE,
                                            "com.thelvm.touchless",
                                            "/com/thelvm/touchless",
                                            sigc::ptr_fun(proxy_created));

  gestureParser.LoadGesturesFromDir(std::string(getenv("HOME")) + "/.touchless/gestures");
  gestureParser.Start();

  auto main_loop = Glib::MainLoop::create();
  main_loop->run();

  return 0;
}