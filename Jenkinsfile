pipeline {
  agent any
  stages {
    stage('build') {
      steps {
          cmakeBuild(
            generator: 'Ninja',
            buildDir: 'Build',
            installation: 'InSearchPath'
          )
      }
    }
  }
}