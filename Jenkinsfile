pipeline {
  agent any
  stages {
    stage('build') {
      steps {
          cmakeBuild(
            generator: 'Ninja',
            buildDir: 'Build',
            sourceDir: 'Source',
            installation: 'InSearchPath'
          )
      }
    }
  }
}