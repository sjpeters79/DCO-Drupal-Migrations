<?php
/**
 * @file
 * drupalcamp_migrate.users.inc
 */

class MigrateContentUsersMigration extends Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);


    $this->description = 'Migrate drupalcamp demo users from json to drupal';
    // Document the source fields
    $fields = array(
      'uuid' => 'Unique ID for each source data row',
      'email' => 'Email',
      'username' => 'same as Email',
    );
    // Second parameter is the unique ID from the source file
    $json_file = dirname(__FILE__) . '/resources/events.json';
    $this->source = new MigrateSourceList(new DrupalCampUsersListJSON($json_file), new DrupalCampUsersItemJSON($json_file, array()), $fields);

    $this->destination = new MigrateDestinationUser();

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'uid' => array('type' => 'varchar',
          'length' => '255',
          'not null' => TRUE,
          'description' => 'User ID'),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $this->addFieldMapping('mail', 'email');
    $this->addFieldMapping('uuid', 'uuid');
    $this->addFieldMapping('name', 'fullName');
    $this->addFieldMapping('pass')->defaultValue($this->RandomString());
    $this->addFieldMapping('status')->defaultValue('1');

    //2 = authenticated user
    $this->addFieldMapping('roles')->defaultValue(array('2'));
  }

  public function RandomString() {
    $characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    $randString = '';
    for ($i = 0; $i < 128; $i++) {
      $randString .= $characters[rand(0, strlen($characters)-1)];
    }
    return $randString;
  }
}

class DrupalCampUsersItemJSON extends MigrateItemJSON {
  protected $data = array();

  public function getItem($id) {
    $obj = parent::getItem($id);
    $item = $obj->$id->contact;
    $obj = new stdClass();

    $obj->email = $item->email;
    $obj->uuid = $id;
    $obj->fullName = $item->first_name . ' ' . $item->last_name;

    return $obj;
  }
}

class DrupalCampUsersListJSON extends MigrateListJSON {

  protected function getIDsFromJSON(array $data) {
    return array_keys($data);
  }
}
