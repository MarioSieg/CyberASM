pipeline {
  agent any
  stages {
    stage('build') {
      steps {
          cmakeBuild(
            installation: 'InSearchPath'
          )
          bat 'cmake -E env LDFLAGS="-fuse-ld=lld-link"'
          bat 'cmake --build . --parallel 8 -G Ninja -Bbuild ' +
          '-DCMAKE_C_COMPILER:PATH="%ProgramFiles%\LLVM\bin\clang.exe" ' +
          '-DCMAKE_CXX_COMPILER:PATH="%ProgramFiles%\LLVM\bin\clang.exe" ' +
          '-DCMAKE_C_COMPILER_ID="Clang" ' +
          '-DCMAKE_CXX_COMPILER_ID="Clang" ' +
          ' -DCMAKE_SYSTEM_NAME="Generic"'
      }
    }
  }
}