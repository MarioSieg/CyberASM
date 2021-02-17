pipeline {
  agent any
  stages {
    stage('build') {
      steps {
          cmakeBuild(
            installation: 'InSearchPath'
          )
          bat 'cmake -T"LLVM-vs2014" --build . --parallel 8'
      }
    }
  }
}