#include "shell.h"

/**
 * get_special - wrapper for get_special static var
 * Return: address of shellvar special
 */
ShellVar **get_special()
{
	static ShellVar *special;

	return (&special);
}
/**
 * getsvars - get static vars wrapper
 * Return: address of var
 */
ShellVar **get_vars()
{
	static ShellVar *vars;

	return (&vars);
}
