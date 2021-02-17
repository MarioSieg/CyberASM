pipeline {
  agent any
  stages {
    stage('build') {
      steps {
          cmakeBuild(
            installation: 'InSearchPath'
          )
          bat 'set C=clang'
          bat 'set CXX=clang++'
          bat 'cmake --build . --parallel 8'
      }
    }
  }
}