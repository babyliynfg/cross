package org.CrossApp.lib;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.content.ContentResolver;
import android.database.Cursor;
import android.provider.ContactsContract;
import android.provider.ContactsContract.CommonDataKinds.Nickname;
import android.provider.ContactsContract.Contacts;
import android.provider.ContactsContract.Data;
import android.util.Log;

public class CrossAppPersonList {
	private static Activity s_pContext;

	public static void Init(final Activity context) {
		s_pContext = context;
	}

	public static class FriendData {
		public String name;
		public ArrayList<String> phoneNumber = new ArrayList<String>();
		public String emailValue;
		public String address_street;
		public String address_city;
		public String address_region;
		public String address_postCode;
		public String address_formatAddress;
		public String nickname;
		public String firstLetter;
	}

	private static native void getPersonList(String personList);

	public static void getPersonList() {
//		 Log.d("ceshi", "通讯录1");
		ArrayList<FriendData> vecFriend = new ArrayList<FriendData>();
		// 联系人集合
		ContentResolver resolver = s_pContext.getContentResolver();
		// 搜索字段//尽量不用嵌套搜索，性能过低
		String[] projection = new String[] {
				ContactsContract.CommonDataKinds.Phone.CONTACT_ID,
				ContactsContract.CommonDataKinds.Phone.NUMBER,
				ContactsContract.Contacts.DISPLAY_NAME,
//				ContactsContract.CommonDataKinds.Email.DATA,
//				ContactsContract.CommonDataKinds.StructuredPostal.STREET,
//				ContactsContract.CommonDataKinds.StructuredPostal.CITY,
//				ContactsContract.CommonDataKinds.StructuredPostal.REGION,
//				ContactsContract.CommonDataKinds.StructuredPostal.POSTCODE,
//				ContactsContract.CommonDataKinds.StructuredPostal.FORMATTED_ADDRESS,
//				ContactsContract.CommonDataKinds.Nickname.DATA,
				ContactsContract.Contacts.SORT_KEY_PRIMARY };

		// 获取手机联系人
		Cursor contactsCursor = resolver.query(
				ContactsContract.CommonDataKinds.Phone.CONTENT_URI, projection,
				null, null, ContactsContract.Contacts.SORT_KEY_PRIMARY);
		if (contactsCursor.moveToFirst()) {
			// key: contactId,value: 该contactId在联系人集合data的index
			Map<Integer, Integer> contactIdMap = new HashMap<Integer, Integer>();
			while (contactsCursor.moveToNext()) {
				// 获取联系人的ID
				int contactId = contactsCursor.getInt(0);
				// 获取联系人的号码
				String phoneNumber = contactsCursor.getString(1);
				// 获取联系人的姓名
				String name = contactsCursor.getString(2);
//				// 获取联系人的邮箱
//				String email = contactsCursor.getString(3);
//				// 获取联系人的街道
//				String street = contactsCursor.getString(4);
//				// 获取联系人的城市
//				String city = contactsCursor.getString(5);
//				// 获取联系人的REGION
//				String region = contactsCursor.getString(6);
//				// 获取联系人的POSTCODE
//				String postcode = contactsCursor.getString(7);
//				// 获取联系人的FORMATTED_ADDRESS
//				String formatted_address = contactsCursor.getString(8);
//				// 获取联系人的Nickname
//				String nickName = contactsCursor.getString(9);
				// 获取联系人的全拼
				String sortkey = contactsCursor.getString(3);

				
				// 号码处理
				String replace = phoneNumber.replace(" ", "").replace("-", "")
						.replace("+", "");
				// 判断号码是否符合手机号
				if (replace.length() > 0) {
					// 如果联系人Map已经包含该contactId
					if (contactIdMap.containsKey(contactId)) {
						// 得到该contactId在data的index
						Integer index = contactIdMap.get(contactId);
						// 重新设置号码数组
						FriendData contacts = vecFriend.get(index);
						contacts.phoneNumber.add(replace);
					} else {
						FriendData contacts = new FriendData();
						// 如果联系人Map不包含该contactId
						contacts.phoneNumber.add(phoneNumber);
						contacts.name = name;
//						contacts.emailValue = email;
//						contacts.address_street = street;
//						contacts.address_city = city;
//						contacts.address_region = region;
//						contacts.address_postCode = postcode;
//						contacts.address_formatAddress = formatted_address;
//						contacts.nickname = nickName;
						
						String key = sortkey.substring(0, 1).toUpperCase();
						if (key.matches("[A-Z]")) {
							contacts.firstLetter = key;
						} else {
							contacts.firstLetter = "#";
						}
						
						vecFriend.add(contacts);
						contactIdMap.put(contactId, vecFriend.size() - 1);
					}
				}

			}
			contactsCursor.close();
		}

		//
		//
		//
		//
		//
		//
		//
		//		
//	        Cursor cur = s_pContext.getContentResolver().query(  
//	                ContactsContract.Contacts.CONTENT_URI,  
//	                null,  
//	                null,  
//	                null,  
//	                ContactsContract.Contacts.DISPLAY_NAME  
//	                        + " COLLATE LOCALIZED ASC");  
		 
//	        Cursor cur = s_pContext.getContentResolver().query(  
//	                ContactsContract.Contacts.CONTENT_URI,  
//	                null,  
//	                null,  
//	                null,  
//	                ContactsContract.Contacts.SORT_KEY_PRIMARY);  
//	        
//	        ArrayList<FriendData> vecFriend = new ArrayList<FriendData>();
//	        
//	        
//	        if (cur.moveToFirst())
//	        {
//	            int idColumn = cur.getColumnIndex(ContactsContract.Contacts._ID);  
//	  
//	            int displayNameColumn = cur.getColumnIndex(ContactsContract.Contacts.DISPLAY_NAME);  
//	            int sortkey = cur.getColumnIndex(ContactsContract.Contacts.SORT_KEY_PRIMARY);  
//	  
//	       	    do 
//	       	    {
//	       	    	try
//					{
//		            	FriendData data = new FriendData();
//		            	
//		                String contactId = cur.getString(idColumn);  
//		                 
//		                String disPlayName = cur.getString(displayNameColumn);  
//		                String sortkeypinyin = cur.getString(sortkey);  
//		                
//
//						String key = sortkeypinyin.substring(0, 1).toUpperCase();
//						if (key.matches("[A-Z]")) {
//							data.firstLetter = key;
//						} else {
//							data.firstLetter = "#";
//						}
//		                
//		                data.name = disPlayName;
//		                
//		                int phoneCount = cur.getInt(cur.getColumnIndex(ContactsContract.Contacts.HAS_PHONE_NUMBER));  
//		                
//		                if (phoneCount > 0)
//		                {  
//		                    Cursor phones = s_pContext.getContentResolver().query(  
//		                            ContactsContract.CommonDataKinds.Phone.CONTENT_URI,  
//		                            null,  
//		                            ContactsContract.CommonDataKinds.Phone.CONTACT_ID  
//		                                    + " = " + contactId, null, null);
//		                    
//		                    if (phones.moveToFirst())
//		                    {  
//		                        do
//		                        {   
//		                            String phoneNumber = phones.getString(phones.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER));   
//		                            
//		                            data.phoneNumber.add( phoneNumber );
//		                        }
//		                        while (phones.moveToNext());  
//		                    }
//		                    
//		                    phones.close();
//		                }  
//		  
//		                Cursor emails = s_pContext.getContentResolver().query(  
//		                        ContactsContract.CommonDataKinds.Email.CONTENT_URI,  
//		                        null,  
//		                        ContactsContract.CommonDataKinds.Phone.CONTACT_ID  
//		                                + " = " + contactId, null, null);  
//		                
//		                if (emails.moveToFirst())
//		                {  
//		                    do
//		                    {  
//		                        
//		                        String emailValue = emails.getString(emails.getColumnIndex(ContactsContract.CommonDataKinds.Email.DATA));  
//
//		                        data.emailValue = emailValue;
//		                    }
//		                    while (emails.moveToNext());  
//		                }  
//		                
//		                emails.close();
//		                
//		                Cursor address = s_pContext.getContentResolver().query(  
//		                                ContactsContract.CommonDataKinds.StructuredPostal.CONTENT_URI,  
//		                                null,  
//		                                ContactsContract.CommonDataKinds.Phone.CONTACT_ID  
//		                                        + " = " + contactId, null, null);  
//		                if (address.moveToFirst()) 
//		                {  
//		                    do {  
//		                        
//		                        String street = address.getString(address  
//		                                        .getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.STREET));  
//		                        
//		                        String city = address.getString(address  
//		                                        .getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.CITY));  
//		                        
//		                        String region = address.getString(address  
//		                                        .getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.REGION));  
//		                        
//		                        String postCode = address.getString(address  
//		                                        .getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.POSTCODE)); 
//		                        
//		                        String formatAddress = address.getString(address  
//		                                        .getColumnIndex(ContactsContract.CommonDataKinds.StructuredPostal.FORMATTED_ADDRESS));
//		                        
//		                        data.address_street = street;  
//		                        data.address_city = city;  
//		                        data.address_region = region;  
//		                        data.address_postCode = postCode;  
//		                        data.address_formatAddress = formatAddress;
//		                    } 
//		                    while (address.moveToNext());  
//		                }  
//		                
//		                address.close();
//		                
//		                
//		                Cursor nicknames = s_pContext.getContentResolver().query(  
//		                        Data.CONTENT_URI,  
//		                        new String[] { Data._ID, Nickname.NAME },  
//		                        Data.CONTACT_ID + "=?" + " AND " + Data.MIMETYPE + "='"+ Nickname.CONTENT_ITEM_TYPE + "'",  
//		                        new String[] { contactId }, null);  
//		                
//		                if (nicknames.moveToFirst()) 
//		                {  
//		                    do 
//		                    {  
//		                        String nickname_ = nicknames.getString(nicknames.getColumnIndex(Nickname.NAME));
//	 
//		                        data.nickname = nickname_;
//		                    } 
//		                    while (nicknames.moveToNext());  
//		                } 
//		                
//		                nicknames.close();
//		                
//		                if ( data.name != null )
//		                	vecFriend.add(data);
//
//		        }
//		        catch( Exception e )
//		        {
//		
//		         }
//		   }
//		 while (cur.moveToNext());
//		 }
//		
	        
	        
		try {

			JSONObject personList = new JSONObject();

			JSONArray personArray = new JSONArray();

			for (int i = 0; i < vecFriend.size(); i++) {
				FriendData data = (FriendData) vecFriend.get(i);
				JSONObject person = new JSONObject();
				person.put("name", data.name);
				person.put("address_street",
						data.address_street != null ? data.address_street
								: "null");
				person.put("address_city",
						data.address_city != null ? data.address_city : "null");
				person.put("address_region",
						data.address_region != null ? data.address_region
								: "null");
				person.put("address_postCode",
						data.address_postCode != null ? data.address_postCode
								: "null");
				person.put(
						"address_formatAddress",
						data.address_formatAddress != null ? data.address_formatAddress
								: "null");
				person.put("nickname", data.nickname != null ? data.nickname
						: "null");
				person.put("firstLetter", data.firstLetter != null ? data.firstLetter
						: "null");

				JSONArray phone = new JSONArray();
				for (int j = 0; j < data.phoneNumber.size(); j++) {
					phone.put((String) data.phoneNumber.get(j));
				}

				person.put("phone", phone);

				if (data.emailValue != null)
					person.put("email", data.emailValue);
				personArray.put(person);
			}

			personList.put("person", personArray);
			String ret = personList.toString();
			onReturnPersonList(ret);
		} catch (JSONException ex) {

			throw new RuntimeException(ex);
		}
	}

	public static void onReturnPersonList(final String personList) {
		CrossAppActivity content = (CrossAppActivity) s_pContext;
		content.runOnGLThread(new Runnable() {
			@Override
			public void run() {
				getPersonList(personList);
			}
		});
	}
}
