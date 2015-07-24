<?php
/**
 * @file
 * drupalcamp_migrate.og.inc
 */

class MigrateOgOrg2Migration extends Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->description = 'Migrate drupal camp demo organizations from json to drupal';

    $fields = array(
      'organizationId' => 'Unique identifier',
      'name' => 'Organization Name',
      'emailAddress' => 'Org Email',
      'address' => 'Street Address',
      'city' => 'City address',
      'province' => 'Province',
      'postalCode' => 'postal code',
      'country' => 'country',
      'websiteUrl' => 'organization website url',
      'primaryPhone' => 'primary phone',
      'primaryPhoneExt' => 'primary phone extension',
      'option' => 'organization type',
    );
    // Second parameter is the unique ID from the source file
    $json_file = dirname(__FILE__) . '/resources/orgs.json';

    $this->source = new MigrateSourceList(new DrupalCampOrganizationsListJSON($json_file), new DrupalCampOrganizationsItemJSON($json_file, array()), $fields);

    $this->destination = new MigrateDestinationNode('organizations');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array('type' => 'varchar',
          'length' => '255',
          'not null' => TRUE,
          'description' => 'Organization ID'),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // Organic Groups
    $this->addFieldMapping('group_group')->defaultValue(1);
    $this->addFieldMapping('og_roles_permissions')->defaultValue(0);

    $this->addFieldMapping('uuid', 'organizationId');
    $this->addFieldMapping('title', 'name');
    $this->addFieldMapping('field_address')->defaultValue('CA');

    $this->addFieldMapping('field_address:locality', 'city');
    $this->addFieldMapping('field_address:postal_code', 'postalCode');
    $this->addFieldMapping('field_address:thoroughfare', 'address');
    $this->addFieldMapping('field_address:administrative_area', 'province');

    $this->addFieldMapping('field_primary_phone', 'primaryPhone');
    $this->addFieldMapping('field_website_url', 'websiteUrl');

    $this->addFieldMapping('field_organization_type', 'option');

    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('uid')->defaultValue(1);

  }
}

class DrupalCampOrganizationsItemJSON extends MigrateItemJSON {
  protected $data = array();

  public function getItem($id) {
    $obj = parent::getItem($id);
    $item = $obj->$id;
    $obj = NULL;

    $ret_obj = $item;
    if (trim($ret_obj->primaryPhoneExt) != '') {
      $ret_obj->primaryPhone = $ret_obj->primaryPhone . ' x' . $ret_obj->primaryPhoneExt;
    }

    $ret_obj->province = $this->getProvinceCode($ret_obj->province);

    $ret_obj->option = $this->getOptionCode($ret_obj->option[0]);

    return $ret_obj;
  }

  private function getOptionCode(stdClass $option) {
    foreach($option as $key => $value) {
      return $key;
    }
  }

  private function getProvinceCode($province) {
    $canadian_province = array(
      "British Columbia" => "BC",
      "Ontario" => "ON",
      "Newfoundland and Labrador" => "NL",
      "Nova Scotia"  => "NS",
      "Prince Edward Island" => "PE",
      "New Brunswick" => "NB",
      "Québec" => "QC",
      "Manitoba" => "MB",
      "Saskatchewan" => "SK",
      "Alberta" => "AB",
      "Northwest Territories" => "NT",
      "Nunavut" => "NU",
      "Yukon Territory" => "YT",
    );
    return isset($canadian_province[$province]) ? $canadian_province[$province] : '';
  }

}

class DrupalCampOrganizationsListJSON extends MigrateListJSON {

  protected function getIDsFromJSON(array $data) {
    return array_keys($data);
  }

}
