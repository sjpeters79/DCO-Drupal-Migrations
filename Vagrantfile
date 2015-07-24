# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"
Vagrant.require_version ">= 1.7.2"
Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.host_name = 'cd6a4c39-a45e-42ec-97bf-23544ee4674d.dropfort.com'
  config.vm.box = "puppetlabs/centos-7.0-64-puppet"
  
  config.vm.network :forwarded_port, guest: 35729, host: 35729, protocol: "tcp"	# Livereload
  config.vm.network :forwarded_port, guest: 80, host: 8080, protocol: "tcp"	# Apache HTTP
  config.vm.network :forwarded_port, guest: 443, host: 8443, protocol: "tcp"	# Apache HTTPS
  config.vm.network :forwarded_port, guest: 3306, host: 3306, protocol: "tcp"	# MySQL
  config.ssh.forward_agent = true
  config.vm.provider :virtualbox do |vb|
    # Use VBoxManage to customize the VM. For example to change memory:
    vb.customize ["modifyvm", :id, "--memory", "1024"]

    # Customize the DNS settings to speed up network requests
    vb.customize ["modifyvm", :id, "--natdnshostresolver1", "on"]
    vb.customize ["modifyvm", :id, "--natdnsproxy1", "on"]
  end
  config.vm.post_up_message = "Provisioned by Dropfort.com"

  config.vm.provision :shell, inline: "if [ ! $(grep single-request-reopen /etc/sysconfig/network) ]; then echo RES_OPTIONS=single-request-reopen >> /etc/sysconfig/network && service network restart; fi"

  # Set puppet keys
  config.vm.provision :shell, inline: "mkdir -p /var/lib/puppet/ssl/private_keys && echo '-----BEGIN PRIVATE KEY-----
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
i27XYHs4QF1VfC4EioiK8gPwsOxR
-----END PRIVATE KEY-----
' > /var/lib/puppet/ssl/private_keys/cd6a4c39-a45e-42ec-97bf-23544ee4674d.dropfort.com.pem
mkdir -p /var/lib/puppet/ssl/public_keys && echo '-----BEGIN PUBLIC KEY-----
MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAs8D7qeoAvfs5bE7biWTh
4+yOfhRuafa1AE3JlB3kxSBRrztVjdLZC8Yiphotyd6Na/8g4WA+TDmvzGmtKxSj
j6Zyi4PYuS+JwWoPJ2BJdxJfUYX/S3Ch3Ry7VMeytivmdyUBSNxCvkVMWvaX2kCg
iiSNxObv5b8W34r4Cx/WNLOVnq2tO63AEs2RJRs0ER3VK4iQ+A81iY4cRBHfvc/W
oI4RvYBcN2RzYyve6JKNZ9MPG1/Tg+TcdWJ7tyCON38/hPXoJJdumIfxD3jhlShG
dtiwahukqRq+4zVX1q72p0Fb5KUbyJ30rGtlZkN10i59BnBVoFiUgFUsHkOGJSEI
ZvyWB4cjwQQyQgn18vPGg1WWPWvRd3/PVL2wKpR5S3GNL5y+BO+jbRjcTtUn64/w
hMGgA0ZcwshvcO7hlQmO/VBMi9zFY8KIQyguKjhqJM5HGTO4sElR5YcIDFNnzhGt
1P4TeA9na7ZW5ww84zkfPOJ/YrEZ3VnuPfqovnLTd59BTGApZX5aagSo98KcAtTA
xzd7dFXpJ4dPAmMyotJiuc3OQj5pFQsxj28Vp3tgnQOfG9S7rGLBs6RTGb949GWC
CNf9M7DvrCIg4WjKyJlTjHONPYnrv9b0XSWGN53J4pvCKR2RUcKmxSbPQydyVqbe
ZC5TqRl1p+9XxEqEeMXp75MCAwEAAQ==
-----END PUBLIC KEY-----
' > /var/lib/puppet/ssl/public_keys/cd6a4c39-a45e-42ec-97bf-23544ee4674d.dropfort.com.pem
"
  # Set puppet master
  config.vm.provision "puppet_server" do |puppet|
    puppet.puppet_server = "provisioner.dropfort.com"
    puppet.puppet_node = "cd6a4c39-a45e-42ec-97bf-23544ee4674d.dropfort.com"
    puppet.options = "--verbose --waitforcert=15 --pluginsync --configtimeout=10m --environment dropfort"
  end
end