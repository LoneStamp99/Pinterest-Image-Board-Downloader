import os
import requests
from bs4 import BeautifulSoup
from tqdm import tqdm

def download_images_from_board(board_url, download_path):
    # Create the download directory if it doesn't exist
    os.makedirs(download_path, exist_ok=True)

    # Retrieve the HTML content of the Pinterest board
    response = requests.get(board_url)
    soup = BeautifulSoup(response.content, 'html.parser')

    # Find all the image tags on the board
    image_tags = soup.find_all('img')

    # Download the images
    for img_tag in tqdm(image_tags, desc='Downloading', unit='image'):
        image_url = img_tag['src']
        image_name = image_url.split('/')[-1]
        image_path = os.path.join(download_path, image_name)

        try:
            # Download the image
            response = requests.get(image_url)
            response.raise_for_status()

            # Save the image to the specified path
            with open(image_path, 'wb') as file:
                file.write(response.content)

            print(f"Download Successful: {image_name}")
        except Exception as e:
            print(f"Download Unsuccessful: {image_name}")
            print(f"Error: {str(e)}")

# Prompt the user to enter the Pinterest board link and download path
board_link = input("Enter Pinterest board link: ")
download_path = input("Enter the download path: ")

# Call the function to start downloading the images
download_images_from_board(board_link, download_path)
