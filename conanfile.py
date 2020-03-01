from conans import ConanFile, CMake, tools


class LogginghConan(ConanFile):
    name = "logging.h"
    version = "0.0.2"
    license = "LICENSE.txt"
    author = "Arwed Mett arwed.mett@googlemail.com"
    url = "https://gitea.metthub.de/Pfeifenjoy/logging.h"
    description = "A very simple logging library which provides colored output."
    topics = ("logging")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"

    def source(self):
        self.run("git clone https://gitea.metthub.de/Pfeifenjoy/logging.h.git")

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="logging.h")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include/logging", src="logging.h")
        self.copy("*logging.h.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["logging.h"]

