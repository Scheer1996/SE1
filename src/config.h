/** ****************************************************************
 * @file    config.h
 ******************************************************************
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * threshold for considering two measurements as different.
 *
 * meant to counteract noise.
 */
constexpr int ALLOWED_HEIGHT_DEVIATION = 29;

/**
 * height measurement of the belt (with no part on it)
 */
constexpr int BELT_HEIGHT = 3780;

#endif /* CONFIG_H */
