pipeline {
  agent any
  stages {
    stage('build') {
        script {
            cmakeBuild
              generator: 'Visual Studio 16 2019',
              buildDir: 'Build',
              sourceDir: '',
              installation: 'InSearchPath',
              steps: [
                  [args: 'all install', envVars: 'DESTDIR=${WORKSPACE}/artifacts']
              ]
        }
      }
    }
  }
}