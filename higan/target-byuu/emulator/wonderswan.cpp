#include <ws/interface/interface.hpp>

struct WonderSwan : Emulator {
  WonderSwan();
  auto load() -> void override;
  auto open(higan::Node::Object, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> override;
  auto input(higan::Node::Input) -> void override;
};

WonderSwan::WonderSwan() {
  interface = new higan::WonderSwan::WonderSwanInterface;
  name = "WonderSwan";
  extensions = {"ws"};
}

auto WonderSwan::load() -> void {
  if(auto port = root->find<higan::Node::Port>("Cartridge Slot")) {
    auto peripheral = port->allocate();
    port->connect(peripheral);
  }
}

auto WonderSwan::open(higan::Node::Object node, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> {
  if(name == "manifest.bml") return Emulator::manifest();

  if(node->identity() == "System" && name == "boot.rom") {
    return vfs::memory::file::open(Resource::WonderSwan::Boot, sizeof Resource::WonderSwan::Boot);
  }

  if(node->identity() == "System" && name == "save.eeprom") {
    return {};
  }

  auto document = BML::unserialize(game.manifest);
  auto programROMSize = document["game/board/memory(content=Program,type=ROM)/size"].natural();
  auto saveRAMVolatile = document["game/board/memory(content=Save)/volatile"];

  if(name == "program.rom") {
    return vfs::memory::file::open(game.image.data(), programROMSize);
  }

  if(name == "save.ram" || name == "save.eeprom") {
    if(saveRAMVolatile) return {};
    string location = {Location::notsuffix(game.location), ".sav"};
    if(auto result = vfs::fs::file::open(location, mode)) return result;
  }

  if(name == "time.rtc") {
    string location = {Location::notsuffix(game.location), ".rtc"};
    if(auto result = vfs::fs::file::open(location, mode)) return result;
  }

  return {};
}

auto WonderSwan::input(higan::Node::Input node) -> void {
  auto name = node->name();
  maybe<InputMapping&> mapping;
  if(name == "Y1"   ) mapping = virtualPad.l1;
  if(name == "Y2"   ) mapping = virtualPad.l2;
  if(name == "Y3"   ) mapping = virtualPad.r1;
  if(name == "Y4"   ) mapping = virtualPad.r2;
  if(name == "X1"   ) mapping = virtualPad.up;
  if(name == "X2"   ) mapping = virtualPad.right;
  if(name == "X3"   ) mapping = virtualPad.down;
  if(name == "X4"   ) mapping = virtualPad.left;
  if(name == "B"    ) mapping = virtualPad.a;
  if(name == "A"    ) mapping = virtualPad.b;
  if(name == "Start") mapping = virtualPad.start;

  if(mapping) {
    auto value = mapping->value();
    if(auto button = node->cast<higan::Node::Button>()) {
      button->setValue(value);
    }
  }
}

struct WonderSwanColor : Emulator {
  WonderSwanColor();
  auto load() -> void override;
  auto open(higan::Node::Object, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> override;
  auto input(higan::Node::Input) -> void override;
};

WonderSwanColor::WonderSwanColor() {
  interface = new higan::WonderSwan::WonderSwanColorInterface;
  name = "WonderSwan Color";
  extensions = {"wsc"};
}

auto WonderSwanColor::load() -> void {
  if(auto port = root->find<higan::Node::Port>("Cartridge Slot")) {
    auto peripheral = port->allocate();
    port->connect(peripheral);
  }
}

auto WonderSwanColor::open(higan::Node::Object node, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> {
  if(name == "manifest.bml") return Emulator::manifest();

  if(node->identity() == "System" && name == "boot.rom") {
    return vfs::memory::file::open(Resource::WonderSwanColor::Boot, sizeof Resource::WonderSwanColor::Boot);
  }

  if(node->identity() == "System" && name == "save.eeprom") {
    return {};
  }

  auto document = BML::unserialize(game.manifest);
  auto programROMSize = document["game/board/memory(content=Program,type=ROM)/size"].natural();
  auto saveRAMVolatile = document["game/board/memory(content=Save)/volatile"];

  if(name == "program.rom") {
    return vfs::memory::file::open(game.image.data(), programROMSize);
  }

  if(name == "save.ram" || name == "save.eeprom") {
    if(saveRAMVolatile) return {};
    string location = {Location::notsuffix(game.location), ".sav"};
    if(auto result = vfs::fs::file::open(location, mode)) return result;
  }

  if(name == "time.rtc") {
    string location = {Location::notsuffix(game.location), ".rtc"};
    if(auto result = vfs::fs::file::open(location, mode)) return result;
  }

  return {};
}

auto WonderSwanColor::input(higan::Node::Input node) -> void {
  auto name = node->name();
  maybe<InputMapping&> mapping;
  if(name == "Y1"   ) mapping = virtualPad.l1;
  if(name == "Y2"   ) mapping = virtualPad.l2;
  if(name == "Y3"   ) mapping = virtualPad.r1;
  if(name == "Y4"   ) mapping = virtualPad.r2;
  if(name == "X1"   ) mapping = virtualPad.up;
  if(name == "X2"   ) mapping = virtualPad.right;
  if(name == "X3"   ) mapping = virtualPad.down;
  if(name == "X4"   ) mapping = virtualPad.left;
  if(name == "B"    ) mapping = virtualPad.a;
  if(name == "A"    ) mapping = virtualPad.b;
  if(name == "Start") mapping = virtualPad.start;

  if(mapping) {
    auto value = mapping->value();
    if(auto button = node->cast<higan::Node::Button>()) {
      button->setValue(value);
    }
  }
}

struct PocketChallengeV2 : Emulator {
  PocketChallengeV2();
  auto load() -> void override;
  auto open(higan::Node::Object, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> override;
  auto input(higan::Node::Input) -> void override;
};

PocketChallengeV2::PocketChallengeV2() {
  interface = new higan::WonderSwan::PocketChallengeV2Interface;
  name = "Pocket Challenge V2";
  extensions = {"pc2"};
}

auto PocketChallengeV2::load() -> void {
  if(auto port = root->find<higan::Node::Port>("Cartridge Slot")) {
    auto peripheral = port->allocate();
    port->connect(peripheral);
  }
}

auto PocketChallengeV2::open(higan::Node::Object node, string name, vfs::file::mode mode, bool required) -> shared_pointer<vfs::file> {
  if(name == "manifest.bml") return Emulator::manifest();

  if(node->identity() == "System" && name == "boot.rom") {
    return vfs::memory::file::open(Resource::WonderSwan::Boot, sizeof Resource::WonderSwan::Boot);
  }

  if(node->identity() == "System" && name == "save.eeprom") {
    return {};
  }

  auto document = BML::unserialize(game.manifest);
  auto programROMSize = document["game/board/memory(content=Program,type=ROM)/size"].natural();
  auto saveRAMVolatile = document["game/board/memory(content=Save)/volatile"];

  if(name == "program.rom") {
    return vfs::memory::file::open(game.image.data(), programROMSize);
  }

  if(name == "save.ram" || name == "save.eeprom") {
    if(saveRAMVolatile) return {};
    string location = {Location::notsuffix(game.location), ".sav"};
    if(auto result = vfs::fs::file::open(location, mode)) return result;
  }

  if(name == "time.rtc") {
    string location = {Location::notsuffix(game.location), ".rtc"};
    if(auto result = vfs::fs::file::open(location, mode)) return result;
  }

  return {};
}

auto PocketChallengeV2::input(higan::Node::Input node) -> void {
  auto name = node->name();
  maybe<InputMapping&> mapping;
  if(name == "Up"    ) mapping = virtualPad.up;
  if(name == "Down"  ) mapping = virtualPad.down;
  if(name == "Left"  ) mapping = virtualPad.left;
  if(name == "Right" ) mapping = virtualPad.right;
  if(name == "Pass"  ) mapping = virtualPad.a;
  if(name == "Circle") mapping = virtualPad.b;
  if(name == "Clear" ) mapping = virtualPad.y;
  if(name == "View"  ) mapping = virtualPad.start;
  if(name == "Escape") mapping = virtualPad.select;

  if(mapping) {
    auto value = mapping->value();
    if(auto button = node->cast<higan::Node::Button>()) {
      button->setValue(value);
    }
  }
}