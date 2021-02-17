pipeline {
  agent any
  stages {
    stage('build') {
      steps {
          bat 'cmake -G "Visual Studio 16 2019" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ C:/Program Files/LLVM/bin/'
          cmakeBuild(
            installation: 'InSearchPath'
          )
          bat 'cmake --build . --parallel 8'
      }
    }
  }
}