from distutils.core import setup
import json
import re

def bump_version(config):
  version = config['version']
  version = list(map(int, re.search('(\d+)\.(\d+)\.(\d+)', version).groups()))
  version[2] += 1
  version = "{}.{}.{}".format(*version)
  config['version'] = version

def load_config():
  return json.load(open('config.json','r'))

def save_config(config):
  json.dump(config, open('config.json', 'w'), indent=4)

def main(config):
  setup(
    name = 'meysql',         # How you named your package folder (MyLib)
    packages = ['meysql'],   # Chose the same as "name"
    package_dir={'':'src'},
    version = config['version'],      # Start with a small number and increase it with every change you make
    license='MIT',        # Chose a license from here: https://help.github.com/articles/licensing-a-repository
    description = 'TODO',   # Give a short description about your library
    author = 'Annekin Meyburgh',                   # Type in your name
    author_email = 'annekin001@gmail.com',      # Type in your E-Mail
    url = 'https://github.com/TheKillerAboy/MeySQL',   # Provide either the link to your github or to your website
    # download_url = 'https://github.com/user/reponame/archive/v_01.tar.gz',    # I explain this later on
    keywords = ['sql', 'database'],   # Keywords that define your package best
    # install_requires=[            # I get to this in a second
    #         'PyYAML',
    #     ],
    classifiers=[
      'Development Status :: 3 - Alpha',      # Chose either "3 - Alpha", "4 - Beta" or "5 - Production/Stable" as the current state of your package
      'Intended Audience :: Developers',      # Define that your audience are developers
      'Topic :: Software Development :: Build Tools',
      'License :: OSI Approved :: MIT License',   # Again, pick a license
      'Programming Language :: Python :: 3.9',
    ],
  )

if __name__ == '__main__':
  config = load_config()
  main(config)