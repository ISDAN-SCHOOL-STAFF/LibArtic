#!/bin/sh

# Detect OS
OS="$(uname -s)"

case "$OS" in
    Linux*)
        # Detect package manager
        if [ -x "$(command -v apt-get)" ]; then
            PKG_MANAGER="apt-get"
            INSTALL_CMD="sudo apt-get install -y"
        elif [ -x "$(command -v yum)" ]; then
            PKG_MANAGER="yum"
            INSTALL_CMD="sudo yum install -y"
        elif [ -x "$(command -v pacman)" ]; then
            PKG_MANAGER="pacman"
            INSTALL_CMD="sudo pacman -S --noconfirm"
        else
            echo "Unsupported package manager on Linux."
            exit 1
        fi

        # Check and install SFML
        if ! ldconfig -p | grep -q sfml; then
            echo "SFML not found. Installing SFML..."
            $INSTALL_CMD libsfml-dev
        else
            echo "SFML is already installed."
        fi
        ;;
    Darwin*)
        # macOS
        if [ -x "$(command -v brew)" ]; then
            PKG_MANAGER="brew"
            INSTALL_CMD="brew install"
        else
            echo "Homebrew not found. Please install Homebrew."
            exit 1
        fi

        # Check and install SFML
        if [ ! -d "/usr/local/Cellar/sfml" ] && [ ! -d "/opt/homebrew/Cellar/sfml" ]; then
            echo "SFML not found. Installing SFML..."
            $INSTALL_CMD sfml
        else
            echo "SFML is already installed."
        fi
        ;;
    *)
        echo "Unsupported OS: $OS"
        exit 1
        ;;
esac

exit 0
