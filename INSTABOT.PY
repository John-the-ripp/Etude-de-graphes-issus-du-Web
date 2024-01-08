import time
from selenium import webdriver
from selenium.common import ElementClickInterceptedException
from selenium.webdriver.common.by import By
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.remote.webelement import WebElement
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import requests
from webdriver_manager.chrome import ChromeDriverManager

class InstagramBot:
    def __init__(self, username, password, proxy_list):
        self.username = username
        self.password = password
        self.proxy_list = proxy_list
        self.driver = webdriver.Chrome(ChromeDriverManager().install())
        self.wait = WebDriverWait(self.driver,10)

    def setup_proxy(self, proxy):
        proxy_dict = {
            "http": f"http://{proxy}",
            "https": f"http://{proxy}"
        }
        session = requests.Session()
        session.proxies.update(proxy_dict)
        self.driver = webdriver.Chrome()
        self.driver.session = session
        self.wait = WebDriverWait(self.driver, 10)

    def SCRIPT(self):
        print("")
        print("  _____           _                                    ____        _   ", "*")
        print(" |_   _|         | |                                  |  _ \      | |  ", "*")
        print("   | |  _ __  ___| |_ __ _  __ _ _ __ __ _ _ __ ___   | |_) | ___ | |_ ", "*")
        print("   | | | '_ \/ __| __/ _` |/ _` | '__/ _` | '_ ` _ \  |  _ < / _ \| __|", "*")
        print("  _| |_| | | \__ \ || (_| | (_| | | | (_| c | | | | | | |_) | (_) | |_ ", "*")
        print(" |_____|_| |_|___/\__\__,_|\__, |_|  \__,_|_| |_| |_| |____/ \___/ \__|", "*")
        print("                            __/ |                                      ", "*")
        print("                           |___/                                       ", "*")
        print("# running ....")

    def login(self):
        self.driver.get("https://www.instagram.com/accounts/login")
        time.sleep(10)

        try:
            self.driver.find_element(By.XPATH,
                                     ' /html[@class="_9dls js-focus-visible _aa4c"]/body[@class="_a3wf system-fonts--body segoe"]/div[@class="x1n2onr6 xzkaem6"]/div[@class="x9f619 x1n2onr6 x1ja2u2z"]/div[@class="x78zum5 xdt5ytf xg6iff7 x1n2onr6"]/div[@class="x1uvtmcs x4k7w5x x1h91t0o x1beo9mf xaigb6o x12ejxvf x3igimt xarpa2k xedcshv x1lytzrv x1t2pt76 x7ja8zs x1n2onr6 x1qrby5j x1jfb8zj"]/div[@class="x1qjc9v5 x9f619 x78zum5 xdt5ytf x1iyjqo2 xl56j7k"]/div[@class="x1cy8zhl x9f619 x78zum5 xl56j7k x2lwn1j xeuugli x47corl"]/div[@class="x1ja2u2z x1afcbsf x1a2a7pz x6ikm8r x10wlt62 x71s49j x6s0dn4 x78zum5 xdt5ytf xl56j7k x1n2onr6"]/div[@class="xs83m0k xl56j7k x1sy10c2 x1h5jrl4 xieb3on xmn8rco x1iy3rx x1n2onr6 xo1d8dh x1m7g9aj xy2hj3m xir0mxb x19osjzx x1juhsu6 xnfgh3p x61jkv3 x1u827li xsw4t2s x1u6teax xa8ff0x x1crxz2b xodhs97 xr2spqc"]/div[@class="x7r02ix xf1ldfh x131esax xdajt7p xxfnqb6 xb88tzc xw2csxc x1odjw0f x5fp0pe x5yr21d x19onx9a"]/div[1]/button[@class="_a9-- _a9_0"]').click()
        except:
            pass

        time.sleep(10)

        username_field = self.driver.find_element(By.NAME, "username")
        username_field.click()
        username_field.send_keys(self.username)

        password_field = self.driver.find_element(By.NAME, "password")
        password_field.click()
        password_field.send_keys(self.password)

        connect_button = self.driver.find_element(By.XPATH, '//button[@type="submit"]')
        connect_button.click()
        time.sleep(20)

    def like(self,profile_url,num_photos_to_like) -> bool:
        like_button: WebElement = None
        self.driver.get(profile_url)
        try:
            like_button = self.driver.find_element(By.XPATH, '//span[@class="_aamw"]')
            # like_button_span = like_button.find_element(By.CSS_SELECTOR, '._aame')
            like_button_span = like_button.find_element(By.XPATH, 'div/div/span')
            button_status = like_button_span.find_element(By.TAG_NAME, 'svg').get_attribute('aria-label')
            # like only if not already liked
            if button_status == 'J’aime' or button_status == 'Like':
                like_button.click()

            else:
                print(f'[target:  post already liked')

            if num_photos_to_like > 0:
                next_button = self.driver.find_element(By.XPATH, '//button[@class="_abl-"]')
                next_button.click()

        except ElementClickInterceptedException:
            self.driver.execute_script('arguments[0].click();', like_button)
        except Exception as ex:
            print(str(ex))
            return False
        return True



    def get_number_of_posts(self, profile_url) -> int:
        try:
            print("hh")
            self.driver.get(profile_url)
            time.sleep(10)
            try:
                num_of_posts = self.driver.find_element(By.XPATH, '//span[@class="_ac2a"]').text
                num_of_posts = num_of_posts.replace(',', '')
                print(num_of_posts)
                return int(num_of_posts)
            except:
                print("error")
        except:
            return None

    def follow(self, profile_url) -> bool:
        try:
            self.driver.get(profile_url)
            time.sleep(10)
            checker = self.driver.find_element(By.XPATH, '//button').text
            if checker == 'Suivi(e)':
                print("already followed")
                return True

            following = self.driver.find_element(By.CSS_SELECTOR, '._acan')
            following.click()
            time.sleep(10)
            return True
        except:
            return False

    def story(self, profil_url) -> bool:
        try:
            self.driver.get(profil_url)
            time.sleep(5)
            Story = self.driver.find_element(By.CSS_SELECTOR, '._aarf')
            Story.click()
            time.sleep(3)
            like_story = self.driver.find_element(By.CSS_SELECTOR,
                                                  '._ac13 > span:nth-child(1) > div:nth-child(1) > div:nth-child(1)')
            like_story.click()
            time.sleep(10)


        except:
            return False





    def comment(self, profil_url, message):
        action = ActionChains(self.driver)
        self.driver.get(profil_url)
        time.sleep(10)

        like_button = self.driver.find_element(By.XPATH, '//div[@class="_aagw"]')
        action.double_click(like_button).perform()

        time.sleep(10)

        commenter = WebDriverWait(self.driver, 10).until(EC.element_to_be_clickable((By.XPATH, '//div/textarea')))
        commenter.click()
        commenter.send_keys(message)
        self.wait.until(EC.presence_of_element_located(
            (By.XPATH, '//div[@role="button" and contains(text(), "Publier")]'))).click()

    def close(self):
        self.driver.quit()


if __name__ == "__main__":
    proxies = ['50.217.226.45:80', '50.204.233.30:80', '47.88.3.19:8080', '50.173.157.70:80', '85.26.146.169:80',
               '50.238.154.98:80', '50.218.57.66:80', '85.8.68.2:80', '50.206.111.91:80', '50.200.12.84:80',
               '50.220.211.83:80', '216.137.184.253:80', '50.224.251.205:80', '45.63.25.2:8888', '50.174.7.152:80',
               '50.217.153.79:80', '50.223.129.105:80', '50.221.227.130:80', '50.173.157.79:80', '50.228.83.226:80',
               '50.218.57.65:80', '64.225.8.179:9998', '46.251.22.215:80', '50.217.153.72:80', '50.168.163.180:80',
               '62.141.11.68:80', '50.219.71.167:80', '50.223.129.109:80', '80.120.130.231:80', '50.228.141.101:80',
               '50.168.72.117:80', '50.168.163.179:80', '50.204.219.229:80', '50.204.219.226:80', '24.158.29.166:80',
               '50.237.89.163:80', '82.119.96.254:80', '213.33.2.28:80', '50.237.89.161:80', '107.1.93.222:80',
               '50.171.32.222:80', '66.191.31.158:80', '50.174.7.154:80', '50.220.211.81:80', '50.217.226.46:80',
               '207.2.120.19:80', '50.227.121.37:80', '50.237.89.170:80', '107.1.93.213:80', '50.231.110.26:80',
               '100.19.135.109:80', '50.171.32.231:80', '50.228.141.96:80', '148.76.97.250:80', '50.173.140.138:80',
               '154.3.9.16:8081', '50.217.22.110:80', '194.158.203.14:80', '50.217.226.42:80', '50.204.219.225:80',
               '50.173.140.151:80', '50.227.121.34:80', '50.237.89.162:80', '50.169.62.104:80', '50.206.25.104:80',
               '50.228.141.102:80', '86.57.217.187:3128', '50.217.22.114:80', '50.173.157.76:80', '50.171.2.9:80',
               '50.171.32.228:80', '50.168.163.177:80', '50.168.49.106:80', '50.206.25.108:80', '20.219.118.36:80',
               '77.73.241.154:80', '50.173.140.144:80', '50.171.2.13:80', '50.217.22.105:80', '103.216.103.163:80',
               '50.168.72.116:80', '183.109.80.229:8080', '50.220.211.82:80', '50.237.89.164:80', '50.171.2.8:80',
               '107.1.93.217:80', '107.1.93.212:80', '209.38.254.44:45212', '50.204.190.234:80', '165.154.224.14:80',
               '185.103.128.138:8080', '88.99.21.184:3128', '96.85.127.233:8080', '103.77.60.14:80', '20.44.206.138:80',
               '34.124.154.221:80', '103.133.210.133:80', '196.20.125.149:8083', '46.105.35.193:8080', '41.77.74.33:80',
               '168.0.239.224:8787', '158.69.53.98:9300', '139.162.78.109:8080', '36.68.70.119:8080',
               '167.99.233.58:8080', '103.87.169.194:32650', '106.10.55.212:5200', '91.113.220.210:3128',
               '103.180.198.6:8181', '45.221.220.238:8080', '200.114.65.15:999', '162.144.233.16:80',
               '85.95.239.81:8118', '209.38.250.139:45212', '103.92.26.190:4002', '202.173.220.50:1122',
               '203.89.126.250:80', '47.56.110.204:8989', '103.168.53.53:41367', '117.54.114.100:80',
               '103.141.143.102:41516', '8.209.114.72:3129', '162.240.75.37:80', '43.205.130.161:80',
               '200.25.254.193:54240', '104.248.90.212:80', '41.217.220.69:32650', '158.69.71.245:9300',
               '46.182.6.51:3129', '213.191.194.24:80', '35.240.156.235:8080', '82.165.184.53:80', '13.81.217.201:80',
               '154.118.228.212:80', '110.34.3.229:3128', '185.15.172.212:3128', '87.237.239.95:3128',
               '103.168.53.1:41317', '47.74.152.29:8888', '213.171.44.134:3128', '103.176.108.105:1433',
               '94.100.26.202:80', '146.196.54.75:80', '38.68.14.37:80', '195.133.45.149:7788', '103.134.44.176:8080',
               '64.225.4.29:9865', '202.86.138.18:8080', '64.226.110.184:45212', '23.238.33.186:80',
               '200.7.10.158:8080', '50.217.22.104:80', '50.217.153.78:80', '50.168.72.112:80', '50.223.38.2:80',
               '213.157.6.50:80', '50.217.22.106:80', '50.171.32.227:80', '50.217.153.73:80', '50.171.32.229:80',
               '208.92.193.57:80', '188.166.56.246:80', '50.171.111.26:80', '50.217.226.44:80', '50.122.86.118:80',
               '50.217.226.41:80', '50.217.153.74:80', '50.221.230.186:80', '50.219.71.164:80', '50.223.129.111:80',
               '50.223.129.106:80', '217.76.50.200:8000', '50.168.34.138:80', '50.171.32.224:80', '195.248.240.25:80',
               '50.223.129.110:80', '13.95.173.197:80', '50.171.2.12:80', '190.103.177.131:80', '186.121.235.66:8080',
               '20.219.235.172:3129', '50.217.22.108:80', '50.219.71.170:80', '27.107.27.9:80', '50.218.57.69:80',
               '107.1.93.208:80', '80.228.235.6:80', '50.224.251.204:80', '51.79.206.225:1080', '18.143.215.49:80',
               '50.219.71.162:80', '91.249.134.148:80', '45.77.28.109:8989', '50.220.189.30:80', '45.62.167.249:80',
               '50.228.141.97:80', '8.219.97.248:80', '37.252.7.112:3128', '50.168.163.181:80', '50.218.57.70:80',
               '20.219.180.105:3129', '50.227.121.39:80', '41.207.187.178:80', '50.172.23.10:80', '107.1.93.210:80',
               '50.218.57.68:80', '191.186.106.34:8080', '134.35.113.18:8080', '171.227.1.137:10066',
               '45.171.108.253:999', '103.167.69.101:8080', '103.74.147.26:80', '179.0.98.34:999',
               '197.157.143.50:8080', '38.25.102.2:999', '20.226.35.129:80', '86.57.137.63:2222', '157.245.27.9:3128',
               '162.223.94.164:80', '75.89.101.62:80', '51.75.83.65:8082', '146.196.54.68:80', '58.27.59.249:80',
               '138.201.113.2:3128', '34.146.64.228:3128', '117.54.114.32:80', '146.59.2.185:80', '60.52.61.39:80',
               '47.88.11.3:20201', '118.69.111.51:8080', '103.149.130.38:80', '135.125.68.145:3128',
               '103.141.142.153:41402', '149.102.243.148:12000', '91.92.126.84:3128', '103.155.217.156:41480',
               '103.141.143.1:41485', '181.205.86.66:80', '20.219.178.121:3129', '103.168.53.157:41485',
               '20.204.190.254:3129', '109.74.50.14:21213', '209.38.201.164:45212', '119.8.10.18:7890',
               '115.144.101.201:10001', '50.237.89.166:80', '185.211.133.110:80', '3.111.208.135:80', '50.200.12.85:80',
               '50.217.226.43:80', '107.1.93.211:80', '50.224.251.207:80', '47.74.154.143:8787', '50.227.121.38:80',
               '50.206.111.89:80', '47.90.162.160:8080', '50.171.68.130:80', '200.105.215.22:33630',
               '200.111.132.157:999', '172.104.30.222:8080', '95.0.214.6:8080', '107.1.93.214:80', '50.168.163.166:80',
               '123.202.159.108:80', '143.42.163.193:80', '68.185.57.66:80', '50.227.121.32:80', '50.231.167.218:80',
               '103.163.51.254:80', '0.0.0.0:80', '154.65.39.7:80', '32.223.6.94:80', '50.168.72.115:80',
               '77.52.180.150:80', '50.169.135.10:80', '184.10.84.74:80', '50.223.38.6:80', '107.1.93.221:80',
               '50.237.207.186:80', '50.171.32.230:80', '107.1.93.216:80', '50.171.1.222:80', '50.218.57.71:80',
               '50.217.226.40:80', '50.217.22.111:80', '50.171.32.225:80', '50.227.121.33:80', '190.58.248.86:80',
               '50.206.25.109:80', '50.174.7.153:80', '50.218.57.64:80', '50.202.75.26:80', '107.1.93.220:80',
               '50.173.140.149:80', '50.217.153.76:80', '50.174.7.162:80', '68.188.59.198:80', '50.217.153.77:80',
               '50.239.72.18:80', '50.206.111.90:80']

    bot = InstagramBot("d309eb0b7c@emailboxa.online", "TESTE123456", proxies)

    for proxy in bot.proxy_list:
        try:
            bot.setup_proxy(proxy)
            bot.SCRIPT()
            bot.login()
            bot.follow("https://www.instagram.com/shot_timeless_/")
            bot.like("https://www.instagram.com/shot_timeless_/", 2)
            #bot.get_number_of_posts("https://www.instagram.com/mmauncensored__/")
            #bot.story("https://www.instagram.com/mmauncensored__/")
            #bot.comment("https://www.instagram.com/guilit_nseka/", "gozaym")
            bot.close()
        except Exception as e:
            print(f"Error with proxy {proxy}: {str(e)}")
            continue