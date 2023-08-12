require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))
folly_compiler_flags = '-DFOLLY_NO_CONFIG -DFOLLY_MOBILE=1 -DFOLLY_USE_LIBCPP=1 -Wno-comma -Wno-shorten-64-to-32'

Pod::Spec.new do |s|
  s.name         = "react-native-tutk-camera" # 模块名称
  s.version      = package["version"] # 模块版本号
  s.summary      = package["description"] # 简要描述
  s.homepage     = package["homepage"] # 项目主页
  s.license      = package["license"] # 开源协议
  s.authors      = package["author"] # 配置作者的信息

  s.platforms    = { :ios => "11.0" }
  s.source       = { :git => "https://github.com/xiaofeifei-sudo/react-native-tutk-camera.git", :tag => "#{s.version}" }
  
#  s.requires_arc = false

  
  s.source_files = "ios/**/*.{h,m,mm,cpp,c}"
  s.exclude_files = "ios/JKCameraModel/LocalRecorder/JKLocalRecorder.m"
  
  
  s.subspec 'no-arc' do |sp|
      sp.source_files = 'ios/JKCameraModel/LocalRecorder/JKLocalRecorder.m'
      sp.requires_arc = false
  end
  
  

  
  
#  s.source_files = {
#    "ios/JKCameraModel/LocalRecorder/JKLocalRecorder.m", :compiler_flags => '-fno-objc-arc'
#  }

#  s.compiler_flags = "-fno-objc-arc"
  
#  s.frameworks = "CoreTelephony"
#  s.weak_framework = "CoreTelephony", "Accelerate", "SystemConfiguration"

#s.compiler_flags = {'ios/JKCameraModel/LocalRecorder/JKLocalRecorder.m' => '-f-no-objc-arc', 'ios/**/*' => '-O0'} //此方法无法禁用arc

  

  
  s.ios.frameworks = "Accelerate","SystemConfiguration","CoreTelephony", "Security", "CoreLocation", "CoreGraphics", "OpenAL", "OpenGLES", "VideoToolbox", "CoreFoundation", "AVFoundation", "AVKit", "Foundation"
  
  s.ios.libraries = "z", "iconv", "bz2", "c++", "sqlite3"
  
  s.vendored_frameworks = "ios/Libs/lib_sync_3.3.5.0/Release-iphoneos/IOTCamera.framework"
  
  s.vendored_libraries = "ios/Libs/**/*.{a}"

  # Use install_modules_dependencies helper to install the dependencies if React Native version >=0.71.0.
  #Seehttps://github.com/facebook/react-native/blob/febf6b7f33fdb4904669f99d795eba4c0f95d7bf/scripts/cocoapods/new_architecture.rb#L79.
  if respond_to?(:install_modules_dependencies, true)
    install_modules_dependencies(s)
  else
  s.dependency "React-Core"
  
#  s.frameworks = "CoreTelephony", "OpenAL"
#
#  s.libraries = "c++", "sqlite3.0", "z"

#  s.libraries = [
#  "ios/Libs/lib_h265_1.0/Release-iphoneos/libCameraSDK.a",
#  "ios/Libs/lib_sync_3.3.0.1/Release-iphoneos/***.framework",
#
#  ]


  


  # Don't install the dependencies when we run `pod install` in the old architecture.
  if ENV['RCT_NEW_ARCH_ENABLED'] == '1' then
    s.compiler_flags = folly_compiler_flags + " -DRCT_NEW_ARCH_ENABLED=1"
    s.pod_target_xcconfig    = {
        "HEADER_SEARCH_PATHS" => "\"$(PODS_ROOT)/boost\"",
        "OTHER_CPLUSPLUSFLAGS" => "-DFOLLY_NO_CONFIG -DFOLLY_MOBILE=1 -DFOLLY_USE_LIBCPP=1",
        "CLANG_CXX_LANGUAGE_STANDARD" => "c++17"
    }
    s.dependency "React-RCTFabric"
    s.dependency "React-Codegen"
    s.dependency "RCT-Folly"
    s.dependency "RCTRequired"
    s.dependency "RCTTypeSafety"
    s.dependency "ReactCommon/turbomodule/core"
   end
  end    
end
