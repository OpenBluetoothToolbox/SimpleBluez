from conans import ConanFile, CMake, tools
from conans.errors import ConanException
import os

class SimpleBlueZ(ConanFile):
   name = "simplebluez"
   license = "MIT"
   description = "A simple C++ wrapper around Bluez with a commercially-friendly licence"
   settings = "os", "compiler", "build_type", "arch"
   requires = "simpledbus/2.1.1"
   options = {
      "log_level": ["VERBOSE_3","VERBOSE_2","VERBOSE_1","VERBOSE_0","DEBUG","INFO","WARNING","ERROR","FATAL"],
      "shared": [True, False]
   }
   default_options = {
      "fmt:header_only" : True,
      "log_level" : "FATAL"
   }
   generators = ["cmake_find_package","cmake"]
   
   exports_sources = "CMakeLists.txt", "include/*",  "src/*",  "examples/*"

   def build(self):
      cmake = CMake(self)
      cmake.definitions["SIMPLEBLUEZ_LOG_LEVEL"] = self.options.log_level
      cmake.definitions["CONAN_BUILD"] = True
      cmake.configure()
      cmake.build()

   def package(self):
        self.copy("*.h", dst="include", src="include")
        if self.options.shared == True:
           self.copy("*.so", dst="lib", keep_path=False)
        else:
           self.copy("*.a", dst="lib", keep_path=False)
        self.copy("*", dst="bin", src="examples/list_adapters/bin", keep_path=False)
        self.copy("*", dst="bin", src="examples/list_paired/bin", keep_path=False)
        self.copy("*", dst="bin", src="examples/scan/bin", keep_path=False)
        self.copy("*", dst="bin", src="examples/connect/bin", keep_path=False)
        self.copy("*", dst="bin", src="examples/pair/bin", keep_path=False)
        self.copy("*", dst="bin", src="examples/read/bin", keep_path=False)
        self.copy("*", dst="bin", src="examples/notify/bin", keep_path=False)
        self.copy("*", dst="bin", src="examples/ble_nus/bin", keep_path=False)

   def package_info(self):
      self.cpp_info.libs = tools.collect_libs(self)
   
   def deploy(self):
      self.copy("*", dst="bin", src="bin")
