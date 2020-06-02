#!/usr/bin/env bash

# Based on:
# Bash Boilerplate: https://github.com/alphabetum/bash-boilerplate

set -o nounset
set -o errexit

trap 'echo "Aborting due to errexit on line $LINENO. Exit code: $?" >&2' ERR

set -o errtrace
set -o pipefail
IFS=$'\n\t'

###############################################################################
# Globals
###############################################################################

# $_VERSION
#
# Manually set this to to current version of the program. Adhere to the
# semantic versioning specification: http://semver.org
_VERSION="0.0.1"

# $DEFAULT_COMMAND
#
# The command to be run by default, when no command name is specified. If the
# environment has an existing $DEFAULT_COMMAND set, then that value is used.
DEFAULT_COMMAND="${DEFAULT_COMMAND:-help}"

###############################################################################
# Debug
###############################################################################

# _debug()
#
# Usage:
#   _debug printf "Debug info. Variable: %s\\n" "$0"
#
# A simple function for executing a specified command if the `$_USE_DEBUG`
# variable has been set. The command is expected to print a message and
# should typically be either `echo`, `printf`, or `cat`.
__DEBUG_COUNTER=0
_debug() {
  if [[ "${_USE_DEBUG:-"0"}" -eq 1 ]]
  then
    __DEBUG_COUNTER=$((__DEBUG_COUNTER+1))
    {
      # Prefix debug message with "bug (U+1F41B)"
      printf "🐛  %s " "${__DEBUG_COUNTER}"
      "${@}"
      printf "―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\\n"
    } 1>&2
  fi
}
# debug()
#
# Usage:
#   debug "Debug info. Variable: $0"
#
# Print the specified message if the `$_USE_DEBUG` variable has been set.
#
# This is a shortcut for the _debug() function that simply echos the message.
debug() {
  _debug echo "${@}"
}

###############################################################################
# Die
###############################################################################

# _die()
#
# Usage:
#   _die printf "Error message. Variable: %s\\n" "$0"
#
# A simple function for exiting with an error after executing the specified
# command. The command is expected to print a message and should typically
# be either `echo`, `printf`, or `cat`.
_die() {
  # Prefix die message with "cross mark (U+274C)", often displayed as a red x.
  printf "❌  "
  "${@}" 1>&2
  exit 1
}
# die()
#
# Usage:
#   die "Error message. Variable: $0"
#
# Exit with an error and print the specified message.
#
# This is a shortcut for the _die() function that simply echos the message.
die() {
  _die echo "${@}"
}

###############################################################################
# Options
#
# NOTE: The `getops` builtin command only parses short options and BSD `getopt`
# does not support long arguments (GNU `getopt` does), so the most portable
# and clear way to parse options is often to just use a `while` loop.
#
# For a pure bash `getopt` function, try pure-getopt:
#   https://github.com/agriffis/pure-getopt
#
# More info:
#   http://wiki.bash-hackers.org/scripting/posparams
#   http://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html
#   http://stackoverflow.com/a/14203146
#   http://stackoverflow.com/a/7948533
#   https://stackoverflow.com/a/12026302
#   https://stackoverflow.com/a/402410
###############################################################################

# Get raw options for any commands that expect them.
_RAW_OPTIONS="${*:-}"

# Parse Options ###############################################################

# Initialize $_COMMAND_ARGV array
#
# This array contains all of the arguments that get passed along to each
# command. This is essentially the same as the program arguments, minus those
# that have been filtered out in the program option parsing loop. This array
# is initialized with $0, which is the program's name.
_COMMAND_ARGV=("${0}")
# Initialize $_CMD and `$_USE_DEBUG`, which can continue to be blank depending
# on what the program needs.
_CMD=""
_USE_DEBUG=0

while [[ ${#} -gt 0 ]]
do
  __opt="${1}"
  shift
  case "${__opt}" in
    -h|--help)
      _CMD="help"
      ;;
    --version)
      _CMD="version"
      ;;
    --debug)
      _USE_DEBUG=1
      ;;
    *)
      # The first non-option argument is assumed to be the command name.
      # All subsequent arguments are added to $_COMMAND_ARGV.
      if [[ -n "${_CMD}" ]]
      then
        _COMMAND_ARGV+=("${__opt}")
      else
        _CMD="${__opt}"
      fi
      ;;
  esac
done

# Set $_COMMAND_PARAMETERS to $_COMMAND_ARGV, minus the initial element, $0. This
# provides an array that is equivalent to $* and $@ within each command
# function, though the array is zero-indexed, which could lead to confusion.
#
# Use `unset` to remove the first element rather than slicing (e.g.,
# `_COMMAND_PARAMETERS=("${_COMMAND_ARGV[@]:1}")`) because under bash 3.2 the
# resulting slice is treated as a quoted string and doesn't easily get coaxed
# into a new array.
_COMMAND_PARAMETERS=("${_COMMAND_ARGV[@]}")
unset "_COMMAND_PARAMETERS[0]"

_debug printf "\${_CMD}: %s\\n" "${_CMD}"
_debug printf "\${_RAW_OPTIONS} (one per line):\\n%s\\n" "${_RAW_OPTIONS}"
_debug printf "\${_COMMAND_ARGV[*]}: %s\\n" "${_COMMAND_ARGV[*]}"
_debug printf \
  "\${_COMMAND_PARAMETERS[*]:-}: %s\\n" \
  "${_COMMAND_PARAMETERS[*]:-}"

###############################################################################
# Environment
###############################################################################

# $_ME
#
# Set to the program's basename.
_ME=$(basename "${0}")

_debug printf "\${_ME}: %s\\n" "${_ME}"

###############################################################################
# Load Commands
###############################################################################

# Initialize $_DEFINED_COMMANDS array.
_DEFINED_COMMANDS=()

# _load_commands()
#
# Usage:
#   _load_commands
#
# Loads all of the commands sourced in the environment.
_load_commands() {

  _debug printf "_load_commands(): entering...\\n"
  _debug printf "_load_commands() declare -F:\\n%s\\n" "$(declare -F)"

  # declare is a bash built-in shell function that, when called with the '-F'
  # option, displays all of the functions with the format
  # `declare -f function_name`. These are then assigned as elements in the
  # $function_list array.
  local _function_list
  _function_list=($(declare -F))

  _debug printf \
    "_load_commands() \${_function_list[@]}: %s\\n" \
    "${_function_list[@]}"

  for __name in "${_function_list[@]}"
  do
    _debug printf \
      "_load_commands() \${__name}: %s\\n" \
      "${__name}"
    # Each element has the format `declare -f function_name`, so set the name
    # to only the 'function_name' part of the string.
    local _function_name
    _function_name=$(printf "%s" "${__name}" | awk '{ print $3 }')

    _debug printf \
      "_load_commands() \${_function_name}: %s\\n" \
      "${_function_name}"

    # Add the function name to the $_DEFINED_COMMANDS array unless it starts
    # with an underscore or is one of the desc(), debug(), or die() functions,
    # since these are treated as having 'private' visibility.
    if ! { [[ "${_function_name}" =~ ^_(.*)  ]] || \
           [[ "${_function_name}" == "desc"  ]] || \
           [[ "${_function_name}" == "debug" ]] || \
           [[ "${_function_name}" == "die"   ]] || \
           [[ "${_function_name}" == "shell_session_update" ]]
    }
    then
      _DEFINED_COMMANDS+=("${_function_name}")
    fi
  done

  _debug printf \
    "commands() \${_DEFINED_COMMANDS[*]:-}:\\n%s\\n" \
    "${_DEFINED_COMMANDS[*]:-}"
}

###############################################################################
# Main
###############################################################################

# _main()
#
# Usage:
#   _main
#
# The primary function for starting the program.
#
# NOTE: must be called at end of program after all commands have been defined.
_main() {
  _debug printf "main(): entering...\\n"
  _debug printf "main() \${_CMD} (upon entering): %s\\n" "${_CMD}"

  # If $_CMD is blank, then set to `$DEFAULT_COMMAND`
  if [[ -z "${_CMD}" ]]
  then
    _CMD="${DEFAULT_COMMAND}"
  fi

  # Load all of the commands.
  _load_commands

  # If the command is defined, run it, otherwise return an error.
  if _contains "${_CMD}" "${_DEFINED_COMMANDS[@]:-}"
  then
    # Pass all comment arguments to the program except for the first ($0).
    ${_CMD} "${_COMMAND_PARAMETERS[@]:-}"
  else
    _die printf "Unknown command: %s\\n" "${_CMD}"
  fi
}

###############################################################################
# Utility Functions
###############################################################################

# _function_exists()
#
# Usage:
#   _function_exists "possible_function_name"
#
# Returns:
#   0  If a function with the given name is defined in the current environment.
#   1  If not.
#
# Other implementations, some with better performance:
# http://stackoverflow.com/q/85880
_function_exists() {
  [ "$(type -t "${1}")" == 'function' ]
}

# _command_exists()
#
# Usage:
#   _command_exists "possible_command_name"
#
# Returns:
#   0  If a command with the given name is defined in the current environment.
#   1  If not.
#
# Information on why `hash` is used here:
# http://stackoverflow.com/a/677212
_command_exists() {
  hash "${1}" 2>/dev/null
}

# _contains()
#
# Usage:
#   _contains "${item}" "${list[@]}"
#
# Returns:
#   0  If the item is included in the list.
#   1  If not.
_contains() {
  local _query="${1:-}"
  shift

  if [[ -z "${_query}"  ]] ||
     [[ -z "${*:-}"     ]]
  then
    return 1
  fi

  for __element in "${@}"
  do
    [[ "${__element}" == "${_query}" ]] && return 0
  done

  return 1
}

# _join()
#
# Usage:
#   _join "," a b c
#   _join "${an_array[@]}"
#
# Returns:
#   The list or array of items joined into a string with elements divided by
#   the optional separator if one is provided.
#
# More information:
#   https://stackoverflow.com/a/17841619
_join() {
  local _delimiter="${1}"
  shift
  printf "%s" "${1}"
  shift
  printf "%s" "${@/#/${_delimiter}}" | tr -d '[:space:]'
}

# _command_argv_includes()
#
# Usage:
#   _command_argv_includes "an_argument"
#
# Returns:
#   0  If the argument is included in `$_COMMAND_ARGV`, the program's command
#      argument list.
#   1  If not.
#
# This is a shortcut for simple cases where a command wants to check for the
# presence of options quickly without parsing the options again.
_command_argv_includes() {
  _contains "${1}" "${_COMMAND_ARGV[@]}"
}

# _blank()
#
# Usage:
#   _blank "$an_argument"
#
# Returns:
#   0  If the argument is not present or null.
#   1  If the argument is present and not null.
_blank() {
  [[ -z "${1:-}" ]]
}

# _present()
#
# Usage:
#   _present "$an_argument"
#
# Returns:
#   0  If the argument is present and not null.
#   1  If the argument is not present or null.
_present() {
  [[ -n "${1:-}" ]]
}

# _interactive_input()
#
# Usage:
#   _interactive_input
#
# Returns:
#   0  If the current input is interactive (eg, a shell).
#   1  If the current input is stdin / piped input.
_interactive_input() {
  [[ -t 0 ]]
}

# _piped_input()
#
# Usage:
#   _piped_input
#
# Returns:
#   0  If the current input is stdin / piped input.
#   1  If the current input is interactive (eg, a shell).
_piped_input() {
  ! _interactive_input
}

###############################################################################
# desc
###############################################################################

# desc()
#
# Usage:
#   desc <name> <description>
#   desc --get <name>
#
# Options:
#   --get  Print the description for <name> if one has been set.
#
# Examples:
# ```
#   desc "list" <<HEREDOC
# Usage:
#   ${_ME} list
#
# Description:
#   List items.
# HEREDOC
#
# desc --get "list"
# ```
#
# Set or print a description for a specified command or function <name>. The
# <description> text can be passed as the second argument or as standard input.
#
# To make the <description> text available to other functions, `desc()` assigns
# the text to a variable with the format `$___desc_<name>`.
#
# When the `--get` option is used, the description for <name> is printed, if
# one has been set.
#
# NOTE:
#
# The `read` form of assignment is used for a balance of ease of
# implementation and simplicity. There is an alternative assignment form
# that could be used here:
#
# var="$(cat <<'HEREDOC'
# some message
# HEREDOC
# )
#
# However, this form appears to require trailing space after backslases to
# preserve newlines, which is unexpected. Using `read` simply requires
# escaping backslashes, which is more common.
desc() {
  _debug printf "desc() \${*}: %s\\n" "$@"
  [[ -z "${1:-}" ]] && _die printf "desc(): No command name specified.\\n"

  if [[ "${1}" == "--get" ]]
  then # get ------------------------------------------------------------------
    [[ -z "${2:-}" ]] && _die printf "desc(): No command name specified.\\n"

    local _name="${2:-}"
    local _desc_var="___desc_${_name}"

    if [[ -n "${!_desc_var:-}" ]]
    then
      printf "%s\\n" "${!_desc_var}"
    else
      printf "No additional information for \`%s\`\\n" "${_name}"
    fi
  else # set ------------------------------------------------------------------
    if [[ -n "${2:-}" ]]
    then # argument is present
      read -r -d '' "___desc_${1}" <<HEREDOC
${2}
HEREDOC

      _debug printf "desc() set with argument: \${___desc_%s}\\n" "${1}"
    else # no argument is present, so assume piped input
      # `read` exits with non-zero status when a delimeter is not found, so
      # avoid errors by ending statement with `|| true`.
      read -r -d '' "___desc_${1}" || true

      _debug printf "desc() set with pipe: \${___desc_%s}\\n" "${1}"
    fi
  fi
}

###############################################################################
# Default Commands
###############################################################################

# Version #####################################################################

desc "version" <<HEREDOC
Usage:
  ${_ME} ( version | --version )

Description:
  Display the current program version.

  To save you the trouble, the current version is ${_VERSION}
HEREDOC
version() {
  printf "%s\\n" "${_VERSION}"
}

# Help ########################################################################

desc "help" <<HEREDOC
Usage:
  ${_ME} help [<command>]

Description:
  Display help information for ${_ME} or a specified command.
HEREDOC
help() {
  if [[ "${1:-}" ]]
  then
    desc --get "${1}"
  else
    cat <<HEREDOC

PathFinding algorithm (A*) library and demo application.
Version: ${_VERSION}

Usage:
  ${_ME} <command> [--command-options] [<arguments>]
  ${_ME} -h | --help
  ${_ME} --version

Options:
  -h --help  Display this help information.
  --version  Display version information.

Help:
  ${_ME} help [<command>]

$(commands)
HEREDOC
  fi
}

# Command List ################################################################

desc "commands" <<HEREDOC
Usage:
  ${_ME} commands [--raw]

Options:
  --raw  Display the command list without formatting.

Description:
  Display the list of available commands.
HEREDOC
commands() {
  if _command_argv_includes "--raw"
  then
    printf "%s\\n" "${_DEFINED_COMMANDS[@]}"
  else
    printf "Available commands:\\n"
    printf "  %s\\n" "${_DEFINED_COMMANDS[@]}"
  fi
}

###############################################################################
# Commands
# ========.....................................................................
#
# Example command group structure:
#
# desc example ""   - Optional. A short description for the command.
# example() { : }   - The command called by the user.
#
#
# desc example <<HEREDOC
#   Usage:
#     $_ME example
#
#   Description:
#     Print "Hello, World!"
#
#     For usage formatting conventions see:
#     - http://docopt.org/
#     - http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap12.html
# HEREDOC
# example() {
#   printf "Hello, World!\\n"
# }
#
###############################################################################

# Example Section #############################################################

# --------------------------------------------------------------------- example

desc "example" <<HEREDOC
Usage:
  ${_ME} example [<name>] [--farewell]

Options:
  --farewell  Print "Goodbye, World!"

Description:
  Print "Hello, World!"
HEREDOC
example() {
  # These debug statements demonstrate the different behaviors of the
  # positional parameters, the special variables, and the two generated
  # command argument arrays.
  #
  # Note in particular that $@ and $* omit the script name like the
  # $_COMMAND_PARAMETERS array does, whereas the positional parameter variables
  # $0, $1, $2 do include it, like the $_COMMAND_ARGV array.
  #
  # Individual elements 0, 1, and 2 of each:
  _debug printf "example() \${0:-}: %s\\n" "${0:-}"
  _debug printf "example() \${_COMMAND_ARGV[0]:-}: %s\\n" "${_COMMAND_ARGV[0]:-}"
  _debug \
    printf "example() \${_COMMAND_PARAMETERS[0]:-}: %s\\n" \
    "${_COMMAND_PARAMETERS[0]:-}"
  _debug printf "example() \${1:-}: %s\\n" "${1:-}"
  _debug printf "example() \${_COMMAND_ARGV[1]:-}: %s\\n" "${_COMMAND_ARGV[1]:-}"
  _debug \
    printf "example() \${_COMMAND_PARAMETERS[1]:-}: %s\\n" \
    "${_COMMAND_PARAMETERS[1]:-}"
  _debug printf "example() \${2:-}: %s\\n" "${2:-}"
  _debug printf "example() \${_COMMAND_ARGV[2]:-}: %s\\n" "${_COMMAND_ARGV[2]:-}"
  _debug \
    printf "example() \${_COMMAND_PARAMETERS[2]:-}: %s\\n" \
    "${_COMMAND_PARAMETERS[2]:-}"
  # Each expanded to string:
  _debug printf "example() \${*:-}: %s\\n" "${*:-}"
  _debug printf "example() \${_COMMAND_ARGV[*]:-}: %s\\n" "${_COMMAND_ARGV[*]:-}"
  _debug \
    printf "example() \${_COMMAND_PARAMETERS[*]:-}: %s\\n" \
    "${_COMMAND_PARAMETERS[*]:-}"

  # Set default greeting.
  local _greeting="Hello"
  # Initialize arguments array.
  local _arguments=()

  # Parse command arguments.
  for __arg in "${_COMMAND_ARGV[@]:-}"
  do
    case ${__arg} in
      --farewell) _greeting="Goodbye";;
      -*) _die printf "Unexpected option: %s\\n" "${__arg}";;
      *) _arguments+=("${__arg}");;
    esac
  done

  _debug printf "example() \${_arguments[0]:-}: %s\\n" "${_arguments[0]:-}"
  _debug printf "example() \${_arguments[1]:-}: %s\\n" "${_arguments[1]:-}"

  local _name=${_arguments[1]:-}

  _debug printf "example() \${greeting}: %s\\n" "${_greeting}"
  _debug printf "example() \${name}: %s\\n" "${_name}"

  if [[ "${_name}" == "Moon" ]]
  then
    printf "%s, Luna!\\n" "${_greeting}"
  elif [[ -n "${_name}" ]]
  then
    printf "%s, %s!\\n" "${_greeting}" "${_name}"
  else
    printf "%s, World!\\n" "${_greeting}"
  fi
}

###############################################################################
# Custom commands
###############################################################################

desc "build" <<HEREDOC
Usage:
  ${_ME} build 

Description:
  Builds "linux.build" folder
HEREDOC
build() {
  cmake --build linux.build
}

# --------------------------------------------------------------------- -------

desc "genmake" <<HEREDOC
Usage:
  ${_ME} genmake

Description:
  Calls CMake to generate makefiles in "linux.build" folder; Previous "linux.build" folder gets deleted.
HEREDOC
genmake() {
  rm -rf ./linux.build
  cmake -S . -B linux.build
}

# --------------------------------------------------------------------- -------

desc "launch" <<HEREDOC
Usage:
  ${_ME} launch

Description:
  Launches demo application from "linux.build" folder
HEREDOC
launch() {
  ./linux.build/demo_app/app/demo_app_basic 
}

# --------------------------------------------------------------------- -------

###############################################################################
# Run Program
###############################################################################

# Call the `_main` function after everything has been defined.
_main
