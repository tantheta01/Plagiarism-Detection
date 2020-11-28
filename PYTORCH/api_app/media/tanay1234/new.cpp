from time import sleep
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
from selenium import webdriver

options = Options()
options.add_argument("--headless")
options.add_argument("window-size=1400,1500")
options.add_argument("--disable-gpu")
options.add_argument("--no-sandbox")
options.add_argument("start-maximized")
options.add_argument("enable-automation")
options.add_argument("--disable-infobars")
options.add_argument("--disable-dev-shm-usage")

driver = webdriver.Chrome(options=options)
# driver.get('https:www.google.com')
sleep(3)

with open("names.txt") as f, open("url.txt", 'a+') as g:
	i=0
	
	for name in f.readlines():
		driver.get('https:www.google.com')
		print(name)
		search_query_ = 'site:linkedin.com/in/ AND "' + name + '"'

		search_query = driver.find_element_by_name('q')
		search_query.send_keys(search_query_)
		sleep(0.5)
		# search_query.send_keys(Keys.RETURN)
		sleep(3)

		linkedin_urls = driver.find_elements_by_class_name('iUh30')
		
		linkedin_urls = [url.text for url in linkedin_urls]
		for url in linkedin_urls:
			if len(url.split())>2:
				g.write(str(i) + " : " + "https://www.linkedin.com/in/" + url.split()[2].strip() + '\n')
		i += 1



driver.quit()




# Expoerience

