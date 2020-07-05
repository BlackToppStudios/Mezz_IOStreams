#!groovy

pipeline {
    agent none
    options {
        buildDiscarder(logRotator(numToKeepStr:'30'))
        timeout(time: 1800, unit: 'SECONDS')
    }
    stages {

        stage('BuildTest') {
            parallel {

                stage('FedoraGcc-Debug') {
                    agent { label "FedoraGcc" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=ON &&
                            ninja &&
                            ./IOStreams_Tester xml &&
                            bash <(curl -s https://codecov.io/bash) -t ${env.CODECOV_TOKEN}
                        """ }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('FedoraGcc-Release') {
                    agent { label "FedoraGcc" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-release'
                        dir('build-release') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja &&
                            ./IOStreams_Tester xml
                        """ }
                    }
                    post {
                        always {
                            junit "build-release/**/Mezz*.xml"
                        }
                    }
                }

                stage('MacOSAir-Debug') {
                    agent { label "MacOSAir" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """#!/bin/bash
                            hostname &&
                            export PATH='$PATH:/usr/local/bin/' &&
                            cmake -G"Xcode" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=ON &&
                            cmake --build . &&
                           ./IOStreams_Tester xml &&
                           bash <(curl -s https://codecov.io/bash) -t ${env.CODECOV_TOKEN}
                        """ }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('MacOSAir-Release') {
                    agent { label "MacOSAir" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-release'
                        dir('build-release') { sh """#!/bin/bash
                            hostname &&
                            export PATH='$PATH:/usr/local/bin/' &&
                            cmake -G"Xcode" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            cmake --build . &&
                           ./IOStreams_Tester xml
                        """ }
                    }
                    post {
                        always {
                            junit "build-release/**/Mezz*.xml"
                        }
                    }
                }

                stage('Raspbian-Debug') {
                    agent { label "Raspbian" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=ON &&
                            ninja &&
                            ./IOStreams_Tester xml &&
                            bash <(curl -s https://codecov.io/bash) -t ${env.CODECOV_TOKEN}
                         """ }
                    }
                    post {
                         always {
                             junit "build-debug/**/Mezz*.xml"
                         }
                    }
                }
                stage('Raspbian-Release') {
                    agent { label "Raspbian" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-release'
                        dir('build-release') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja &&
                            ./IOStreams_Tester xml
                         """ }
                    }
                    post {
                         always {
                             junit "build-release/**/Mezz*.xml"
                         }
                    }
                }

                stage('UbuntuClang-Debug') {
                    agent { label "UbuntuClang" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=ON &&
                            ninja &&
                            ./IOStreams_Tester xml &&
                            valgrind ./IOStreams_Tester &&
                            bash <(curl -s https://codecov.io/bash) -t ${env.CODECOV_TOKEN}
                         """ }
                     }
                     post {
                         always {
                             junit "build-debug/**/Mezz*.xml"
                         }
                     }
                }
                stage('UbuntuClang-Release') {
                    agent { label "UbuntuClang" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-release'
                        dir('build-release') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja  &&
                            ./IOStreams_Tester xml &&
                            valgrind ./IOStreams_Tester
                         """ }
                     }
                     post {
                         always {
                             junit "build-release/**/Mezz*.xml"
                         }
                     }
                }

                stage('UbuntuEmscripten-Debug') {
                    agent { label "UbuntuEmscripten" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """#!/bin/bash
                            hostname &&
                            source ~/emsdk/emsdk_env.sh &&
                            cmake -E env EMCC_DEBUG=2 CXXFLAGS="-fno-var-tracking -s WASM=1" cmake -G"Ninja" .. -DCMAKE_TOOLCHAIN_FILE=~/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_C_COMPILER=emcc -DCMAKE_CXX_COMPILER=em++ -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja &&
                            node IOStreams_Tester.js NoThreads
                        """ }
                    }
                    // Don't capture Emscripten logs, because it cannot make files
                }
                stage('UbuntuEmscripten-Release') {
                    agent { label "UbuntuEmscripten" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-release'
                        dir('build-release') { sh """#!/bin/bash
                            hostname &&
                            source ~/emsdk/emsdk_env.sh &&
                            cmake -E env EMCC_DEBUG=2 CXXFLAGS="-fno-var-tracking -s WASM=1" cmake -G"Ninja" .. -DCMAKE_TOOLCHAIN_FILE=~/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_C_COMPILER=emcc -DCMAKE_CXX_COMPILER=em++ -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja &&
                            node IOStreams_Tester.js NoThreads
                        """ }
                    }
                    // Don't capture Emscripten logs, because it cannot make files
                }

                stage('UbuntuGcc-Debug') {
                    agent { label "UbuntuGcc" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-debug'
                        dir('build-debug') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=ON &&
                            ninja &&
                            ./IOStreams_Tester xml &&
                            valgrind ./IOStreams_Tester &&
                            bash <(curl -s https://codecov.io/bash) -t ${env.CODECOV_TOKEN}
                        """ }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('UbuntuGcc-Release') {
                    agent { label "UbuntuGcc" }
                    steps {
                        checkout scm
                        sh 'mkdir -p build-release'
                        dir('build-release') { sh """#!/bin/bash
                            hostname &&
                            cmake -G"Ninja" .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF &&
                            ninja &&
                            ./IOStreams_Tester xml &&
                            valgrind ./IOStreams_Tester
                        """ }
                    }
                    post {
                        always {
                            junit "build-release/**/Mezz*.xml"
                        }
                    }
                }

                stage('Windows10Mingw32-Debug') {
                    agent { label "Windows10Mingw32" }
                    steps {
                        checkout scm
                        bat 'if not exist "build-debug" mkdir build-debug'
                        dir('build-debug') {
                            bat 'hostname'
                            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF -DMEZZ_ForceGcc32Bit=ON'
                            bat 'ninja'
                            bat 'IOStreams_Tester xml'
                        }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('Windows10Mingw32-Release') {
                    agent { label "Windows10Mingw32" }
                    steps {
                        checkout scm
                        bat 'if not exist "build-release" mkdir build-release'
                        dir('build-release') {
                            bat 'hostname'
                            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF -DMEZZ_ForceGcc32Bit=ON'
                            bat 'ninja'
                            bat 'IOStreams_Tester xml'
                        }
                    }
                    post {
                        always {
                            junit "build-release/**/Mezz*.xml"
                        }
                    }
                }

                stage('Windows10Mingw64-Debug') {
                    agent { label "Windows10Mingw64" }
                    steps {
                        checkout scm
                        bat 'if not exist "build-debug" mkdir build-debug'
                        dir('build-debug') {
                            bat 'hostname'
                            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
                            bat 'ninja'
                            bat 'IOStreams_Tester xml'
                        }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('Windows10Mingw64-Release') {
                    agent { label "Windows10Mingw64" }
                    steps {
                        checkout scm
                        bat 'if not exist "build-release" mkdir build-release'
                        dir('build-release') {
                            bat 'hostname'
                            bat 'cmake -G"Ninja" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
                            bat 'ninja'
                            bat 'IOStreams_Tester xml'
                        }
                    }
                    post {
                        always {
                            junit "build-release/**/Mezz*.xml"
                        }
                    }
                }

                stage('Windows10MSVC-Debug') {
                    agent { label "Windows10MSVC" }
                    steps {
                        checkout scm
                        bat 'if not exist "build-debug" mkdir build-debug'
                        dir('build-debug') {
                            bat 'hostname'
                            bat '"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x86_amd64 && cmake -G"Visual Studio 16 2019 Win64" .. -DCMAKE_BUILD_TYPE=DEBUG -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
                            bat 'cmake --build .'
                            bat 'IOStreams_Tester xml'
                        }
                    }
                    post {
                        always {
                            junit "build-debug/**/Mezz*.xml"
                        }
                    }
                }
                stage('Windows10MSVC-Release') {
                    agent { label "Windows10MSVC" }
                    steps {
                        checkout scm
                        bat 'if not exist "build-release" mkdir build-release'
                        dir('build-release') {
                            bat 'hostname'
                            bat '"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x86_amd64 && cmake -G"Visual Studio 16 2019 Win64" .. -DCMAKE_BUILD_TYPE=RELEASE -DMEZZ_BuildDoxygen=OFF -DMEZZ_CodeCoverage=OFF'
                            bat 'cmake --build .'
                            bat 'IOStreams_Tester xml'
                        }
                    }
                    post {
                        always {
                            junit "build-release/**/Mezz*.xml"
                        }
                    }
                }

            }
        } // BuildTest
    } // Stages

}
