FROM trainiteu/gitpod-cpp

# Add clang apt repositories
RUN lsb_rel=`lsb_release -cs` \
  && sudo add-apt-repository "deb http://apt.llvm.org/${lsb_rel}/ llvm-toolchain-${lsb_rel}-16 main"

# Install older compilers supported by the project
RUN sudo install-packages \
  g++-12 \
  clang-16
