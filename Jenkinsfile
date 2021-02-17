pipeline {
  agent any
  stages {
    stage('build') {
      steps {
          cmakeBuild(
            installation: 'InSearchPath'
          )
          bat 'cmake --build . --parallel 8 -T llvm'
      }
    }
  }
}