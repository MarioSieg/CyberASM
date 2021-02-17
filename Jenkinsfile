pipeline {
  agent any
  stages {
    stage('build') {
      steps {
          bat 'set CC=C:/Program Files/LLVM/bin/clang.exe'
          bat 'set CXX=C:/Program Files/LLVM/bin/clang++.exe'
          cmakeBuild(
            installation: 'InSearchPath'
          )
          bat 'cmake --build . --parallel 8'
      }
    }
  }
}