pipeline {
  agent any
  stages {
    stage('build') {
        script {
            cmakeBuild
              buildDir: 'Build'
        }
      }
    }
  }
}