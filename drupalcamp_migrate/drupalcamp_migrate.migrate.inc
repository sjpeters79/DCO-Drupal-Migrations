<?php

/**
 * @file
 * drupalcamp_migrate.migrate.inc
 */

/**
 * Implements hook_migrate_api().
 *
 * @returns array
 */


function drupalcamp_migrate_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'og' => array(
        'title' => t('Drupal Camp Organic Groups'),
      ),
      'content' => array(
        'title' => t('Drupal Camp Content Type Migrations'),
      ),
    ),
    'migrations' => array(
      'OgGroups' => array(
        'class_name' => 'MigrateOgOrg2Migration',
        'group_name' => 'og',
      ),
      'ContentUsers' => array(
        'class_name' => 'MigrateContentUsersMigration',
        'group_name' => 'content',
      ),
      'ContentEvents' => array(
        'class_name' => 'MigrateContentEventsMigration',
        'group_name' => 'content',
      ),
    ),
  );
  return $api;
}