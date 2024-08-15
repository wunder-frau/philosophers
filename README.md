# 🍽️ Philosophers

*I Never Thought Philosophy Would Be So Deadly* 😱

Welcome to the **Philosophers** project, where deep thinking meets a deadly twist! This project simulates the classic "Dining Philosophers Problem" using multithreading in C. Below, you'll find all the information you need to understand, build, and run the project.

## 📖 Table of Contents

1. [Project Overview](#-project-overview)
2. [Requirements](#-requirements)
3. [Installation](#-installation)
4. [Usage](#-usage)
5. [How It Works](#-how-it-works)

---

## 🌟 Project Overview

The "Dining Philosophers Problem" is a famous problem in computer science that illustrates the challenges of resource sharing and synchronization. In this project, you'll find a solution to this problem, where philosophers sit around a table, alternating between thinking, eating, and possibly dying if they don't eat in time.

## 💻 Requirements

To build and run this project, you will need:

- **C Compiler**: GCC or Clang
- **POSIX Threads Library**: Usually included with GCC/Clang
- **Make**: To automate the build process

## ⚙️ Installation

Clone the repository to your local machine:

```bash
git clone https://github.com/yourusername/philosophers.git
cd philo
```

## 🚀 Usage

Run the program with the following command:

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]
```
## 🎮 How to Use

For example:

```bash
./philo 5 800 200 200
```
This starts a simulation with 5 philosophers, where each philosopher has 800ms to eat before dying, takes 200ms to eat, and 200ms to sleep.
<!--
ls --colour=never src/* | entr sh -c "make && ./philo 3 100 500 300; echo ----"
-->