#!/usr/bin/env bash

# setup-config.sh
echo "Setting up the .git/config file with template repository..."

# Set the template repository details
SOURCE_REPO_URL="https://github.com/uniofgreenwich/MD_Book_Template.git"
SOURCE_BRANCH="main"

# Check if the 'template' remote exists, if not, add it
git remote get-url template &>/dev/null
if [ $? -ne 0 ]; then
  echo "Adding 'template' remote to .git/config..."
  git remote add template "$SOURCE_REPO_URL"
  git config remote.template.fetch "+refs/heads/*:refs/remotes/template/*"
fi

# Fetch the latest changes from the template repository
git fetch template

# Force the update from the template repository (overwrite any conflicts)
git reset --hard template/"$SOURCE_BRANCH"

# Push the changes to the target repository
git push origin "$SOURCE_BRANCH" --force

echo "Target repository updated with template changes and pushed to $SOURCE_BRANCH."
