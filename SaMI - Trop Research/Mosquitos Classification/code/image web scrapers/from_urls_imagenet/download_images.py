import requests
import re

def is_downloadable(url):
    """
    Does the url contain a downloadable resource
    """
    h = requests.head(url, allow_redirects=True)
    header = h.headers
    content_type = header.get('content-type')
    if 'text' in content_type.lower():
        return False
    if 'html' in content_type.lower():
        return False
    return True

def get_filename_from_cd(cd):
    """
    Get filename from content-disposition
    """
    if not cd:
        return None
    fname = re.findall('filename=(.+)', cd)
    if len(fname) == 0:
        return None
    return fname[0]

filename = "aedes.txt"

with open(filename, "r") as urls:
    for url in urls:
        print(url)
        if(is_downloadable(url)):
            try:
                r = requests.get(url, allow_redirects=True)
                filename = get_filename_from_cd(r.headers.get('content-disposition'))
                if filename is None:
                    if url.find('/'):
                        filename = "images/" + url.rsplit('/', 1)[1]
                open(filename, 'wb').write(r.content)
            except Exception as e:
                print(e)

    urls.close()