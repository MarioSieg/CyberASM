pipeline {
  agent any
  stages {
    stage('build') {
      steps {
          bat 'setx CC=C:/Program Files/LLVM/bin/clang.exe'
          bat 'setx CXX=C:/Program Files/LLVM/bin/clang++.exe'
          cmakeBuild(
            installation: 'InSearchPath'
          )
          bat 'cmake --build . --parallel 8'
      }
    }
  }
}