pipeline {
  agent any
  stages {
    stage('build') {
      steps {
          bat 'export CC=C:/Program Files/LLVM/bin/clang.exe'
          bat 'export CXX=C:/Program Files/LLVM/bin/clang++.exe'
          cmakeBuild(
            installation: 'InSearchPath'
          )
          bat 'cmake --build . --parallel 8'
      }
    }
  }
}