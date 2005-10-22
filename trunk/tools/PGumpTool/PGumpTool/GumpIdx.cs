using System;

namespace PGumpTool
{
	
	public class GumpIdx
	{
		int _id;
		byte[] bytes;

		public int ID{
			get{
				return _id;
			}
			set{
				_id=value;
			}
		}
		public uint Lookup{
			get{
				return BitConverter.ToUInt32(bytes,0);
			}
			set{
				byte[] b = BitConverter.GetBytes(value);
				for (int i=0; i<b.Length; i++)
					bytes[i]=b[i];
			}
		}

		public uint Size
		{
			get
			{
				return BitConverter.ToUInt32(bytes,4);
			}
			set{
				byte[] b = BitConverter.GetBytes(value);
				for (int i=0; i<b.Length; i++)
					bytes[i+4]=b[i];
			}
		}

		public ushort Height
		{
			get
			{
				return BitConverter.ToUInt16(bytes,8);
			}
			set{
				byte[] b = BitConverter.GetBytes(value);
				for (int i=0; i<b.Length; i++)
					bytes[i+8]=b[i];
			}
		}

		public ushort Width
		{
			get
			{
				return BitConverter.ToUInt16(bytes,10);
			}
			set{
				byte[] b = BitConverter.GetBytes(value);
				for (int i=0; i<b.Length; i++)
					bytes[i+10]=b[i];
			}
		}

		public GumpIdx(){
			bytes=new byte[12];
		}

		public GumpIdx(int id,byte[] bytes)
		{
			this.bytes=bytes;
			_id=id;
		}

		public override string ToString()
		{
			return "Gump: 0x"+Convert.ToString(_id,16);
		}

	}
}
