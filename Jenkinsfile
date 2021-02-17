pipeline {
  agent any
  stages {
    stage('build') {
      steps {
          cmakeBuild(
            installation: 'InSearchPath'
          )
          bat 'cmake --build ${WORKSPACE} --parallel 8'
      }
    }
  }
}