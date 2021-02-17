pipeline {
  agent any
  stages {
    stage('build') {
      steps {
          cmakeBuild(
            installation: 'InSearchPath'
          )
          bat 'setx C "clang"
          bat 'setx CXX "clang++"
          bat 'cmake --build . --parallel 8'
      }
    }
  }
}